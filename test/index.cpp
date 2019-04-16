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
    std::cout << a << std::endl;
    auto          b = linspace<float>( 0, 1.0, 10, false );
    Tensor<float> bx( {10} );
    bx = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    Tensor<float> bxy( {10} );
    auto          x = bxy.value();
    auto          y = bx.value().array() > 0.2f;
    x               = y;
    std::cout << bxy << std::endl;
}
