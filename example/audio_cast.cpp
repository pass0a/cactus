#define DR_WAV_IMPLEMENTATION
#include "cmdline.hxx"
#include "dir-wav.hxx"
#include "ghc/filesystem.hpp"
#include <string>

namespace fs {
using namespace ghc::filesystem;
} // namespace fs

void wav_cast( const char *src, const char *dst, uint32_t channels,
               uint32_t rate, uint32_t bits ) {
    drwav_data_format format;
    format.container =
        drwav_container_riff; // <-- drwav_container_riff = normal WAV files,
                              // drwav_container_w64 = Sony Wave64.
    format.format =
        DR_WAVE_FORMAT_PCM; // <-- Any of the DR_WAVE_FORMAT_* codes.
    format.channels      = channels;
    format.sampleRate    = (drwav_uint32) rate;
    format.bitsPerSample = bits;
    drwav *pWav          = drwav_open_file_write( dst, &format );
    if ( pWav ) {
        std::ifstream fin( src, std::ios::binary );
        size_t        len = fin.tellg();
        char *        buf = new char[ len ];
        if ( fin.is_open() ) {
            fin.read( buf, len );
            fin.close();
        }
        drwav_uint64 samplesWritten = drwav_write( pWav, len, buf );
        drwav_close( pWav );
        if ( samplesWritten != channels * rate ) {
            std::cerr << "drwav cast error!!!" << std::endl;
        }
    }
}
int main( int argc, char **argv ) {

    cmdline::parser args;

    args.add<std::string>( "src", 's', "src audio'path", true, "./" );
    args.add<std::string>( "dst", 'd', "dst feature'path", true, "./" );
    args.add<uint32_t>( "channels", 'c', "channels", false, 1 );
    args.add<uint32_t>( "rate", 'r', "sampleRate", false, 22050 );
    args.add<uint32_t>( "bits", 'b', "bitsPerSample", false, 16 );
    args.parse_check( argc, argv );
    auto src = fs::path( args.get<std::string>( "src" ) );
    auto dst = fs::path( args.get<std::string>( "dst" ) );
    wav_cast( src.c_str(), dst.c_str(), args.get<uint32_t>( "channels" ),
              args.get<uint32_t>( "rate" ), args.get<uint32_t>( "bits" ) );
    return 0;
}
