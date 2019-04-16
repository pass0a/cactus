#include "../cactus/cactus.hpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

using namespace cactus;

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    Tensor<float> a;
    a      = {1, 2, 3};
    auto z = a * 2;
    REQUIRE( z.ref( {0} ) == 2 );
    REQUIRE( z.ref( {1} ) == 4 );
    REQUIRE( z.ref( {2} ) == 6 );
}
TEST_CASE( "sin", "[sin]" ) {
    int  SAMPLING = 22050;
    int  FFT_SIZE = 512;
    auto a        = arange<float>( 0, 1.0, 0.2 );
    auto b        = linspace<float>( 0, 1.0, 10, false );
    std::cout << b << std::endl;

    Tensor<float> bx( {10} );
    bx     = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    auto z = bx - b;
    std::cout << z << std::endl;
    std::cout << b.ref( {9} ) << bx.ref( {9} ) << std::endl;
}
