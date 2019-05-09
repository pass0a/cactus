
#define DR_WAV_IMPLEMENTATION
#define FMT_HEADER_ONLY

#include "audio_feature.h"
#include "cmdline.hxx"
#include "ghc/filesystem.hpp"
#include <dirent.h>
//#include "dirent.h"
#include "sqlite/sqlite3.h"
#include <fmt/format.h>
#include <fstream>
#include <iostream>

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
int createSql( const char *dbname ) {
    sqlite3 *     db = NULL;
    sqlite3_stmt *stmt;
    sqlite3_open( dbname, &db );
    const char *sql = "create table audio(ID INTEGER PRIMARY KEY AUTOINCREMENT "
                      "NOT NULL, NAME "
                      "TEXT NOT NULL, POS TEXT NOT NULL, FEATURE INT NOT NULL)";

    int rc = sqlite3_prepare( db, sql, -1, &stmt, NULL );
    onError( rc, sqlite3_errmsg( db ) );
    rc = sqlite3_step( stmt );
    onError( rc, sqlite3_errmsg( db ) );
    sqlite3_close( db );
    return 0;
}
int insertSql( const char *dbname, const char *filename,
               std::vector<size_t> f ) {
    sqlite3 *     db = NULL;
    sqlite3_stmt *stmt;
    sqlite3_open( dbname, &db );
    size_t pos = 0;

    const char *sql = "insert into audio values(NULL,?,?,?)";
    int         rc  = 0;
    sqlite3_exec( db, "begin;", 0, 0, 0 );
    rc = sqlite3_prepare_v2( db, sql, -1, &stmt, NULL );
    onError( rc, sqlite3_errmsg( db ) );

    for ( auto fea : f ) {
        rc = sqlite3_reset( stmt );
        rc = sqlite3_bind_text( stmt, 1, filename, -1, SQLITE_STATIC );
        rc = sqlite3_bind_int( stmt, 2, pos );
        rc = sqlite3_bind_int( stmt, 3, fea );
        rc = sqlite3_step( stmt );
        // onError( rc, sqlite3_errmsg( db ) );
        pos++;
    }
    sqlite3_finalize( stmt );
    sqlite3_exec( db, "commit;", 0, 0, 0 );
    sqlite3_close( db );
    return 0;
}
int main( int argc, char **argv ) {

    cmdline::parser args;

    args.add<std::string>( "src", 's', "src audio'path", true, "./" );
    args.add<std::string>( "dst", 'd', "dst feature'path", true, "./" );
    args.parse_check( argc, argv );
    DIR *          dir;
    struct dirent *ent;
    auto path = fs::absolute( fs::path( args.get<std::string>( "src" ) + "/" ) )
                    .generic_string();
    auto dst = fs::path( args.get<std::string>( "dst" ) );
    if ( fs::exists( dst ) ) {
        std::cout << "feature db already exists!!!" << std::endl;
        return 0;
    }
    dir = opendir( path.c_str() );
    std::cout << path << std::endl;

    if ( dir == NULL ) {
        std::cout << path << std::endl;
        return -1;
    }
    createSql( dst.generic_string().c_str() );
    while ( ( ent = readdir( dir ) ) ) {
        if ( !strcmp( ent->d_name + strlen( ent->d_name ) - 4, ".wav" ) ) {
            std::cout << ent->d_name << std::endl;
            auto wavf = path + ent->d_name;
            auto f1   = gen_feature( wavf.c_str() );
            // file = args.get<std::string>( "dst" ) + "/" + ent->d_name +
            // ".data";
            insertSql( dst.generic_string().c_str(), ent->d_name, f1 );
            // std::vector<std::vector<size_t>> fea;
            // for ( int i = 0; i < f1.size() - 2; i++ ) {
            //     std::vector<size_t> tmp;
            //     tmp.emplace_back( f1[ i ] );
            //     tmp.emplace_back( f1[ i + 1 ] );
            //     tmp.emplace_back( f1[ i + 2 ] );
            //     fea.emplace_back( tmp );
            // }
            // auto sf = feature( fea );
            // flist.emplace_back( sf );
            // std::cout << std::bitset<sizeof( uint32_t ) * 8>( sf ) <<
            // std::endl;
        }
    }
    return 0;
}
