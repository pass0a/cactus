
#define DR_WAV_IMPLEMENTATION
#define FMT_HEADER_ONLY

#include "../cactus/cactus.hpp"
#include "cmdline.hxx"
#include "dir-wav.hxx"
#include <fftw3.h>
#include <fmt/format.h>
#include <fstream>
#include <iostream>

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
        drwav_uninit( pWav );
        if ( samplesWritten != totalSampleCount ) {
            fprintf( stderr, "ERROR\n" );
            exit( 1 );
        }
    }
}
int write_file( const char *path, void *data, size_t len ) {
    std::ofstream fout( path, std::ios::binary );
    std::cout << path << "-->" << len << std::endl;
    if ( fout.is_open() ) {
        fout.write( reinterpret_cast<char *>( data ), len );
        fout.close();
        return 0;
    }
    return -1;
}
template <typename T, typename Layout> int plot( tensor<T, Layout> z ) {
    write_file( "tmp.data", z.data(), z.size() * sizeof( T ) );

    auto cmd = fmt::format( "gnuplot -e \"plot 'tmp.data' binary array=({0}) "
                            "format='%float' with lines;pause -1;\"",
                            z.size() );
    return system( cmd.c_str() );
}
void framing( Tensor<float> data, size_t rate, float timeperframe,
              float stride ) {}
template <typename T, typename Layout>
tensor<T, Layout> preprocess( tensor<T, Layout> in ) {
    tensor<T, Layout> tmp( in.shape() );
    auto              z = tmp.subView( {{1, in.size()}} );
    auto              zi =
        in.subView( {{1, in.size()}} ) - in.subView( {{0, in.size() - 1}} );
    z = zi;
    return tmp;
}
int main( int argc, char **argv ) {
    cmdline::parser args;
    Tensor<short>   samples;
    Tensor<float>   out;
    drwav           wav;

    args.add<std::string>( "src", 's', "src audio'path", true, "" );
    args.parse_check( argc, argv );

    if ( !drwav_init_file( &wav, args.get<std::string>( "src" ).c_str() ) ) {
        std::cout << "error in open wav:" << args.get<std::string>( "src" )
                  << std::endl;
    }
    size_t len = wav.totalPCMFrameCount * wav.channels;
    samples.reshape( {len} );
    size_t numberOfSamplesActuallyDecoded = drwav_read_pcm_frames_s16(
        &wav, wav.totalPCMFrameCount, samples.data() );
    std::cout << "samples.len:" << samples.shape()[ 0 ] << std::endl;
    // wavWrite( args.get<std::string>( "dst" ).c_str(), samples.data(),
    //           wav.sampleRate, wav.totalPCMFrameCount );
    auto z = ( samples + 32768 ) / 65535.0f;
    plot( z );
    preprocess( z );
    // framing( z, wav.sampleRate, 0.025, 0.010 );
    // auto z = samples.subView( {{0, 20}} );
    // std::cout << z << std::endl;
    drwav_uninit( &wav );
    return 0;
}
