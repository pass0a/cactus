#ifndef __CACTUS__EIGEN_TOOLS_HPP
#define __CACTUS__EIGEN_TOOLS_HPP
#include "tensor.hpp"

namespace cactus {
template <typename T> Tensor<T> linspace( T start, T end, T step ) {
    Tensor<T> tmp;
    tmp;
    return tmp;
}
template <typename T> Tensor<T> arange( T start, T end, T step = 1 ) {
    assert( step != 0 );
    size_t    num = abs( ( end - start ) / step );
    Tensor<T> tmp( {num} );
    for ( T i = start; i < end; i += step ) {
        tmp.data()[ i ] = i;
    }
    return tmp;
}
} // namespace cactus
#endif
