#include "../cactus/cactus.hpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

using namespace cactus;

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
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    Tensor<float> a;
    a      = {1, 2, 3};
    auto z = a * 2;
    REQUIRE( z.ref( {0} ) == 2 );
    REQUIRE( z.ref( {1} ) == 4 );
    REQUIRE( z.ref( {2} ) == 6 );
}
TEST_CASE( "linspace&arange", "[linspace]" ) {
    auto a = arange<float>( 0, 1.0, 0.1 );
    auto b = linspace<float>( 0, 1.0, 10, false );

    Tensor<float> bx( {10} );
    bx      = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    auto z1 = abs( bx - b ) < 0.0001;
    auto z2 = abs( bx - a ) < 0.0001;
    REQUIRE( min( z1 ) != 0 );
    REQUIRE( min( z2 ) != 0 );
}
TEST_CASE( "sin", "[sin]" ) {
    int  SAMPLING = 22050;
    int  FFT_SIZE = 512;
    auto data_x   = arange<float>( 0, 1.0, 1.0 / SAMPLING );
    auto data_y   = sin( 2 * 3.14159f * data_x );
    std::cout << data_y.subView( {{0, 40}} ) << std::endl;
    write_file( "sin.data", data_y.data(), data_y.size() * sizeof( float ) );
    system( "gnuplot -e \"plot 'sin.data' binary array=(22050) "
            "format='%float' with lines;pause -1;\"" );
}
