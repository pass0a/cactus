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
    auto a        = arange( 0, 1.0, 1.0 / SAMPLING );
    auto z        = a * 2;
    REQUIRE( z.ref( {0} ) == 2 );
    REQUIRE( z.ref( {1} ) == 4 );
    REQUIRE( z.ref( {2} ) == 6 );
}
