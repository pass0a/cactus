#ifndef __CACTUS_SIMHASH_HPP__
#define __CACTUS_SIMHASH_HPP__

#include <stdint.h>
#include <vector>

template <typename T, typename Container = std::vector<T>> class SimHash {
  public:
    SimHash() {}
    uint32_t toHash( Container data ) {
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
        std::fill( std::begin( v ), std::end( v ), 0 );
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
    uint32_t feature( std::vector<Container> in_data ) {
        std::vector<std::pair<uint32_t, int>> tmp;

        for ( auto it : in_data ) {
            tmp.emplace_back( std::make_pair( toHash( it ), 1 ) );
        }
        return simHash( tmp );
    }
    uint32_t feature( Container in_data ) {
        std::vector<std::pair<uint32_t, int>> tmp;

        for ( auto it : in_data ) {
            Container ff;
            ff.push_back( it );
            tmp.push_back( std::make_pair( toHash( ff ), 1 ) );
            ff.clear();
        }
        return simHash( tmp );
    }
};

#endif
