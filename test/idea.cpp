#include "../example/timing.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstddef>
#include <iostream>
#include <vector>
template <typename T> size_t comlen( T *p, size_t plen, T *q, size_t qlen ) {
    size_t len = 0;
    while ( len < plen && len < qlen && *p++ == *q++ ) {
        ++len;
    }
    return len;
}
template <typename T>
std::vector<T> lcs_base( std::vector<T> a, std::vector<T> b ) {
    size_t maxlen   = 0;
    size_t maxindex = 0;
    for ( int i = 0; i < a.size(); ++i ) {
        for ( int j = 0; j < b.size(); ++j ) {
            int len = comlen( &a[ i ], a.size() - i, &b[ j ], b.size() - j );
            if ( len > maxlen ) {
                maxlen   = len;
                maxindex = i;
            }
        }
    }
    std::vector<T> tmp( maxlen );
    std::copy( a.data() + maxindex, a.data() + maxindex + maxlen, tmp.data() );
    return std::move( tmp );
}
TEST_CASE( "lcs_base", "[lcs]" ) {
    auto r = lcs_base<int>( {1, 2, 3}, {2, 3, 4} );
    REQUIRE( r.size() == 2 );
}
