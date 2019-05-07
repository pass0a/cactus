#ifndef __CACTUS__EIGEN_TOOLS_HPP
#define __CACTUS__EIGEN_TOOLS_HPP
#include "common.hpp"
#include <iostream>
namespace cactus {
template <typename T>
Tensor<T> linspace( T start, T stop, size_t len, bool endpoint = true ) {
    switch ( len ) {
    case 0:
        break;
    case 1: {
        Tensor<T> tmp( {len} );
        tmp = {start};
        return std::move( tmp );
    }
    default: {
        T step = 0;
        if ( endpoint ) {
            step = ( stop - start ) / ( len - 1 );
        } else {
            step = ( stop - start ) / len;
        }
        Tensor<T> tmp( {len} );
        for ( int i = 0; i < len; i++ ) {
            tmp.data()[ i ] = i * step;
        }
        return std::move( tmp );
    }
    }
    return Tensor<T>( {0} );
}
template <typename T> Tensor<T> arange( T start, T stop, T step = 1 ) {
    if ( ( step > 0 ) && ( stop < start ) ) {
        std::string errStr = "ERROR: arange: stop value must be larger than "
                             "the start value for positive step.";
        std::cerr << errStr << std::endl;
        throw std::invalid_argument( errStr );
    }

    if ( ( step < 0 ) && ( stop > start ) ) {
        std::string errStr = "ERROR: arange: start value must be larger than "
                             "the stop value for negative step.";
        std::cerr << errStr << std::endl;
        throw std::invalid_argument( errStr );
    }
    if ( step == 0 ) {
        std::string errStr = "ERROR: arange: step must not be zero ";
        std::cerr << errStr << std::endl;
        throw std::invalid_argument( errStr );
    }
    if ( start == stop ) {
        std::string errStr =
            "ERROR: arange: start value & end value must not be equal ";
        std::cerr << errStr << std::endl;
        throw std::invalid_argument( errStr );
    }
    size_t    num = std::abs( std::ceil( ( stop - start ) / step ) );
    Tensor<T> tmp( {num} );
    for ( int i = 0; i < num; i++ ) {
        tmp.data()[ i ] = i * step;
    }
    return std::move( tmp );
}
template <typename T, typename Layout>
std::vector<size_t> argmax( tensor<T, Layout> in ) {
    std::vector<size_t> sh;
    int                 x, y;
    in.value().maxCoeff( &x, &y );
    sh.emplace_back( x );
    sh.emplace_back( y );
    return sh;
}
template <typename T, typename Layout>
std::vector<size_t> argmin( tensor<T, Layout> in ) {
    std::vector<size_t> sh;
    int                 x, y;
    in.value().minCoeff( &x, &y );
    sh.emplace_back( x );
    sh.emplace_back( y );
    return sh;
}
template <typename T, typename Layout> T max( tensor<T, Layout> in ) {
    return in.value().maxCoeff();
}
template <typename T, typename Layout> T min( tensor<T, Layout> in ) {
    return in.value().minCoeff();
}
template <typename D, typename S, typename Layout>
Tensor<D> cast( tensor<S, Layout> in ) {
    Tensor<D> tmp( in.shape() );
    tmp.value() = in.value().template cast<D>();
    return tmp;
}
template <typename T, typename Layout>
Tensor<T> real( tensor<std::complex<T>, Layout> in ) {
    Tensor<T> tmp( in.shape() );
    tmp.value() = in.value().real();
    return tmp;
}
template <typename T, typename Layout>
Tensor<T> imag( tensor<std::complex<T>, Layout> in ) {
    Tensor<T> tmp( in.shape() );
    tmp.value() = in.value().real();
    return tmp;
}
} // namespace cactus
#endif
