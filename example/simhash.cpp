#include "simhash.h"

uint32_t toHash( std::vector<size_t> data ) {
    // BKDRHash
    uint32_t seed = 131; // 31 131 1313 13131 131313 etc..
    uint32_t hash = 0;

    for ( auto it : data ) {
        hash = hash * seed + it;
    }
    return ( hash & 0x7FFFFFFF );
}
uint32_t simHash( std::vector<std::pair<uint32_t, int>> feature ) {
    int v[ 32 ];
    memset( v, 0, sizeof( int ) * 32 );
    for ( auto it : feature ) {
        for ( size_t j = 0; j < 32; j++ ) {
            v[ j ] += ( it.first & ( 1 << j ) ) ? it.second : -it.second;
        }
    }
    uint32_t hash = 0;
    for ( size_t i = 0; i < 32; i++ ) {
        if ( v[ i ] > 0 ) {
            hash |= ( 1 << i );
        }
    }
    return hash;
}
uint32_t hanming_distance( uint32_t c1, uint32_t c2 ) {
    uint32_t v = c1 ^ c2, dist = 0;
    while ( v ) {
        v = v & ( v - 1 );
        dist++;
    }
    return dist;
}
uint32_t feature( std::vector<std::vector<size_t>> in_data ) {
    std::vector<std::pair<uint32_t, int>> tmp;

    for ( auto it : in_data ) {
        tmp.emplace_back( std::make_pair( toHash( it ), 1 ) );
    }
    return simHash( tmp );
}
uint32_t feature( std::vector<size_t> in_data ) {
    std::vector<std::pair<uint32_t, int>> tmp;

    for ( auto it : in_data ) {
        std::vector<size_t> ff;
        ff.emplace_back( it );
        tmp.emplace_back( std::make_pair( toHash( ff ), 1 ) );
    }
    return simHash( tmp );
}
