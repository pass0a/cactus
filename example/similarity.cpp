#define DR_WAV_IMPLEMENTATION
#define WITHOUT_NUMPY
#include "../cactus/cactus.hpp"
#include "cmdline.hxx"
#include "dir-wav.hxx"
#include "mathplotlibcpp.h"
#include <fftw3.h>
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

int main( int argc, char **argv ) {
    cmdline::parser args;
    Tensor<float>   samples, out;
    drwav           wav;

    args.add<std::string>( "src", 's', "src audio'path", true, "" );
    args.add<std::string>( "dst", 'd', "dst audio'path", true, "" );
    args.parse_check( argc, argv );

    if ( !drwav_init_file( &wav, args.get<std::string>( "src" ).c_str() ) ) {
        std::cout << "error in open wav:" << args.get<std::string>( "src" )
                  << std::endl;
    }
    size_t len = wav.totalPCMFrameCount * wav.channels;
    samples.reshape( {len} );
    size_t numberOfSamplesActuallyDecoded = drwav_read_pcm_frames_f32(
        &wav, wav.totalPCMFrameCount, samples.data() );
    std::cout << numberOfSamplesActuallyDecoded << std::endl;
    // wavWrite( args.get<std::string>( "dst" ).c_str(), samples.data(),
    //           wav.sampleRate, wav.totalPCMFrameCount );

    fftwf_plan p = fftwf_plan_dft_r2c_1d(
        wav.sampleRate, samples.data(),
        reinterpret_cast<fftwf_complex *>( out.data() ), FFTW_ESTIMATE );
    fftwf_execute( p ); /* repeat as needed */
    fftwf_destroy_plan( p );
    // auto z = samples.subView( {{0, 20}} );
    // std::cout << z << std::endl;
    drwav_uninit( &wav );
    return 0;
}
