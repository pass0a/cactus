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
    size_t    num = abs( ceil( ( stop - start ) / step ) );
    Tensor<T> tmp( {num} );
    for ( int i = 0; i < num; i++ ) {
        tmp.data()[ i ] = i * step;
    }
    return std::move( tmp );
}
} // namespace cactus
#endif
