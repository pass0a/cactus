#define DR_WAV_IMPLEMENTATION
#define FMT_HEADER_ONLY

#include "../cactus/cactus.hpp"
#include "cmdline.hxx"
#include "dir-wav.hxx"
#include "ghc/filesystem.hpp"
#include <dirent.h>
//#include "dirent.h"
#include "sqlite/sqlite3.h"
#include <fftw3.h>
#include <fmt/format.h>
#include <iostream>
#include <set>

using namespace cactus;

Tensor<float> hamming( size_t num ) {
    auto tmp = linspace<size_t>( 0, num, num );
    return 0.53836f - 0.46164f * cos( ( 2 * 3.14159f * tmp ) / ( num - 1 ) );
}
Tensor<std::complex<float>> fft( Tensor<float> in_data ) {
    Tensor<std::complex<float>> out_data( {in_data.size()} );
    fftwf_plan                  p = fftwf_plan_dft_r2c_1d(
        in_data.size(), in_data.data(),
        reinterpret_cast<fftwf_complex *>( out_data.data() ), FFTW_ESTIMATE );
    fftwf_execute( p );
    fftwf_destroy_plan( p );
    return out_data;
}
/*
  framing
  start i(framelen-framestride) to framelen+i(framelen-framestride) for per
  frame
*/
std::vector<size_t> framing( Tensor<float> data, size_t rate, size_t time,
                             size_t stride ) {
    size_t framelen    = rate / 1000 * time;
    size_t framestride = rate / 1000 * stride;
    size_t len = ( data.size() - framelen ) / ( framelen - framestride );
    std::cout << data.size() << ":"
              << framelen + len * ( framelen - framestride ) << std::endl;
    std::vector<size_t> feature;
    for ( size_t i = 0; i < len; i++ ) {
        auto tmp =
            1 * data.subView( {{i * ( framelen - framestride ), framelen}} );
        auto mag_frames = abs( real( fft( tmp * hamming( framelen ) ) ) );
        auto pow_frames = ( ( 1.0f / framelen ) * pow( mag_frames, 2 ) );
        auto pos        = argmax( pow_frames.subView( {{0, 180}} ) );
        feature.emplace_back( pos[ 0 ] );
        // if ( i == 12 ) {
        //     plot( mag_frames );
        //     plot( pow_frames );
        //     plot( tmp );
        //     // plot( mag_frames );
        // }
    }
    return feature;
}
Tensor<float> normalize( Tensor<short> data ) {
    // return ( data + 32768 ) / 65535.0f;
    return data * 1.0f / ( max( abs( data ) ) );
}
template <typename T, typename Layout>
tensor<T, Layout> pre_emphasis( tensor<T, Layout> data ) {
    tensor<T, Layout> tmp( data.shape() );
    tmp.subView( {{1, data.size() - 1}} ) =
        data.subView( {{1, data.size() - 1}} ) -
        ( data.subView( {{0, data.size() - 1}} ) * 0.97f );
    return tmp;
}
std::vector<size_t> genfeature( const char *path ) {
    Tensor<short> samples;
    Tensor<float> out;
    drwav         wav;

    if ( !drwav_init_file( &wav, path ) ) {
        std::cout << "error in open wav:" << path << std::endl;
    }
    size_t len = wav.totalPCMFrameCount * wav.channels;
    samples.reshape( {len} );
    size_t numberOfSamplesActuallyDecoded = drwav_read_pcm_frames_s16(
        &wav, wav.totalPCMFrameCount, samples.data() );
    std::cout << "samples.len:" << samples.shape()[ 0 ] << std::endl;
    // wavWrite( args.get<std::string>( "dst" ).c_str(), samples.data(),
    //           wav.sampleRate, wav.totalPCMFrameCount );

    // plot( samples, "short" );
    auto x = normalize( samples );
    // plot( x );
    auto tmp = pre_emphasis( x );
    // plot( tmp );
    auto feature = framing( tmp, wav.sampleRate, 25, 20 );

    // auto z = samples.subView( {{0, 20}} );
    // std::cout << z << std::endl;
    drwav_uninit( &wav );
    return std::move( feature );
}
namespace fs {
using namespace ghc::filesystem;
} // namespace fs

int main( int argc, char **argv ) {
    cmdline::parser args;

    args.add<std::string>( "src", 's', "src audio'path", true, "./" );
    args.add<std::string>( "dst", 'd', "dst feature'path", true, "./" );
    args.parse_check( argc, argv );
    auto srcfile = fs::path( args.get<std::string>( "src" ) );
    if ( !fs::is_regular_file( srcfile ) ) {
        return 0;
    }
    auto             f1 = genfeature( srcfile.generic_string().c_str() );
    std::set<size_t> fset;
    for ( auto t : f1 ) {
        fset.insert( t );
    }
    std::cout << fset.size() << std::endl;
    return 0;
}
