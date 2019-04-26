#define FMT_HEADER_ONLY

#include "audio_feature.h"
#include "cmdline.hxx"
#include "ghc/filesystem.hpp"
#include <dirent.h>
//#include "dirent.h"
#include "sqlite/sqlite3.h"
#include <fmt/format.h>
#include <iostream>
#include <set>

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
