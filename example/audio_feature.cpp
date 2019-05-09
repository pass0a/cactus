#include "audio_feature.h"

#define DR_WAV_IMPLEMENTATION
#include "../cactus/cactus.hpp"
#include "dir-wav.hxx"
#include <fftw3.h>
#include <fstream>

using namespace cactus;

void wavWrite( const char *filename, const void *buffer, int sampleRate,
               uint32_t totalSampleCount ) {
    drwav_data_format format;
    format.container =
        drwav_container_riff; // <-- drwav_container_riff = normal WAV files,
                              // drwav_container_w64 = Sony Wave64.
    format.format =
        DR_WAVE_FORMAT_PCM; // <-- Any of the DR_WAVE_FORMAT_* codes.
    format.channels      = 1;
    format.sampleRate    = (drwav_uint32) sampleRate;
    format.bitsPerSample = 16;
    drwav *pWav          = drwav_open_file_write( filename, &format );
    if ( pWav ) {
        drwav_uint64 samplesWritten =
            drwav_write( pWav, totalSampleCount, buffer );
        drwav_close( pWav );
        if ( samplesWritten != totalSampleCount ) {
            fprintf( stderr, "ERROR\n" );
            exit( 1 );
        }
    }
}
int write_vector( const char *path, std::vector<size_t> data ) {
    std::ofstream f( path, std::ios::out | std::ofstream::binary );
    for ( auto it = data.begin(); it != data.end(); it++ ) {
        f << *it << std::endl;
    }
    f.close();
    return 0;
}

int write_file( const char *path, void *data, size_t len ) {
    std::ofstream fout( path, std::ios::binary );
    if ( fout.is_open() ) {
        fout.write( reinterpret_cast<char *>( data ), len );
        fout.close();
        return 0;
    }
    return -1;
}
template <typename T, typename Layout>
int plot( tensor<T, Layout> z, const char *format = "float" ) {
    write_file( "tmp.data", z.data(), z.size() * sizeof( T ) );

    auto cmd = fmt::format( "gnuplot -e \"plot 'tmp.data' binary array=({0}) "
                            "format='%{1}' with lines;pause -1;\"",
                            z.size(), format );
    return system( cmd.c_str() );
}
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
    // std::cout << data.size() << ":"
    // << framelen + len * ( framelen - framestride ) << std::endl;
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
std::vector<size_t> gen_feature( const char *path ) {
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
    // std::cout << "samples.len:" << samples.shape()[ 0 ] << std::endl;
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
