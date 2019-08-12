#define FMT_HEADER_ONLY

#include "audio_feature.h"
#include "cmdline.hxx"
#include "ghc/filesystem.hpp"
//#include "dirent.h"
#include "sqlite/sqlite3.h"
#include <fmt/format.h>
#include <iostream>
#include <map>
#include <set>

namespace fs {
using namespace ghc::filesystem;
} // namespace fs
void onError( int code, const char *info ) {
    switch ( code ) {
    case SQLITE_OK:
    case SQLITE_ROW:
    case SQLITE_DONE:
        break;
    default:
        std::cout << code << ":" << info << std::endl;
        break;
    }
}
int queryFeature( const char *dbname, std::set<size_t> fset ) {
    sqlite3 *     db = NULL;
    sqlite3_stmt *stmt;
    sqlite3_open( dbname, &db );

    const char *sql =
        "select NAME,count(*) from audio where feature==? group by NAME;";
    int rc = 0;
    sqlite3_exec( db, "begin;", 0, 0, 0 );
    rc = sqlite3_prepare_v2( db, sql, -1, &stmt, NULL );
    onError( rc, sqlite3_errmsg( db ) );
    const char *                  p;
    int                           nums;
    std::map<std::string, size_t> result;

    for ( auto f : fset ) {
        rc = sqlite3_reset( stmt );
        rc = sqlite3_bind_int( stmt, 1, f );
        rc = sqlite3_step( stmt );
        if (f) {
            while (rc == SQLITE_ROW) {
                p = (const char *)sqlite3_column_text(stmt, 0);
                nums = sqlite3_column_int(stmt, 1);
                std::cout << f << ":" << p << "--" << nums << std::endl;
                result[p] += nums;
                rc = sqlite3_step(stmt);
            }
        }
        
        // onError( rc, sqlite3_errmsg( db ) );
    }
    sqlite3_finalize( stmt );
    sqlite3_exec( db, "commit;", 0, 0, 0 );
    sqlite3_close( db );
    /*auto x = std::max_element( result.begin(), result.end(),
                               []( const std::pair<std::string, int> &p1,
                                   const std::pair<std::string, int> &p2 ) {
                                   return p1.second < p2.second;
                               } );*/
    for (auto x:result)
    {
        std::cout << x.first << x.second << std::endl;
    }
    return 0;
}
int main( int argc, char **argv ) {
    cmdline::parser args;

    args.add<std::string>( "src", 's', "src audio'path", true, "./" );
    args.add<std::string>( "dst", 'd', "dst feature'path", true, "./" );
    args.parse_check( argc, argv );
    auto srcfile = fs::path( args.get<std::string>( "src" ) );
    auto dst     = fs::path( args.get<std::string>( "dst" ) );

    if ( !fs::is_regular_file( srcfile ) ) {
        return 0;
    }
    auto             f1 = gen_feature( srcfile.generic_string().c_str() );
    std::set<size_t> fset;
    for ( auto t : f1 ) {
        fset.insert( t );
    }
    std::cout << fset.size() << std::endl;
    queryFeature( dst.generic_string().c_str(), fset );
    return 0;
}
