#include "../cactus/cactus.hpp"
#define CATCH_CONFIG_MAIN
#define FMT_HEADER_ONLY
#include "catch.hpp"
#include <fftw3.h>
#include <fmt/format.h>
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
TEST_CASE( "subview", "[subview]" ) {
    auto x = linspace<float>( 0, 1, 10 );
    auto y = x.subView( {{0, 5}} );
    auto z = x.subView( {{5, 5}} );
    y      = z;
    std::cout << x << std::endl;
}
TEST_CASE( "sin", "[sin]" ) {
    int                         SAMPLING = 22050;
    int                         FFT_SIZE = 512;
    Tensor<std::complex<float>> out( {22050} );
    auto                        data_x = linspace<float>( 0, 1.0, SAMPLING );
    auto                        data_y = sin( 2 * 3.14159f * data_x );
    write_file( "sin.data", data_y.data(), data_y.size() * sizeof( float ) );
    // auto cmd = fmt::format( "gnuplot -e \"plot 'sin.data' binary array=({0})
    // "
    //                         "format='%float' with lines;pause -1;\"",
    //                         20 );
    // system( cmd.c_str() );
    fftwf_plan p = fftwf_plan_dft_r2c_1d(
        data_y.size(), data_y.data(),
        reinterpret_cast<fftwf_complex *>( out.data() ), FFTW_ESTIMATE );
    fftwf_execute( p );
    fftwf_destroy_plan( p );
    auto fftw_out = real( out );
    write_file( "fft.data", fftw_out.data(),
                fftw_out.size() * sizeof( float ) );
    // cmd = fmt::format( "gnuplot -e \"plot 'fft.data' binary array=({0}) "
    //                    "format='%float' with lines;pause -1;\"",
    //                    SAMPLING );
    // system( cmd.c_str() );
}
