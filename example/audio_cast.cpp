#define DR_WAV_IMPLEMENTATION
#include "cmdline.hxx"
#include "dir-wav.hxx"
#include "ghc/filesystem.hpp"
#include <string>

namespace fs {
using namespace ghc::filesystem;
} // namespace fs

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
int main( int argc, char **argv ) {

    cmdline::parser args;

    args.add<std::string>( "src", 's', "src audio'path", true, "./" );
    args.add<std::string>( "dst", 'd', "dst feature'path", true, "./" );
    args.add<int>( "type", "t", "file type", false, 0 );
    args.add<int>( "channels", 'c', "channels", false, 1 );
    args.add<int>( "rate", 'r', "sampleRate", false, 22050 );
    args.add<int>( "bits", 'b', "bitsPerSample", false, 16 );
    args.parse_check( argc, argv );
    auto src = fs::path( args.get<std::string>( "src" ) );
    auto dst = fs::path( args.get<std::string>( "dst" ) );

    return 0;
}
