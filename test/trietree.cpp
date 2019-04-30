#define CATCH_CONFIG_MAIN

#include "../cactus/algorithm/trietree.hpp"
#include "../cactus/algorithm/simhash.hpp"
#include "../cactus/algorithm/suffixtree.hpp"
#include "catch.hpp"
#include <iostream>
#include <string>
TEST_CASE( "Tree", "[Tree]" ) {
    TreeNode<char> tmp( 'a' );
    TreeNode<char> b( 'b' );
    TreeNode<char> c( 'c' );
    TreeNode<char> d( 'd' );
    b.add( c );
    d.add( TreeNode<char>( 'e' ) );
    tmp.add( b );
    tmp.add( d );
    Tree<char>                 t;
    auto                       dfs = t.dfs( tmp );
    auto                       bfs = t.bfs( tmp );
    SimHash<char, std::string> sh;
    std::string                buf;
    for ( auto v : dfs ) {
        buf.push_back( v.value );
    }
    REQUIRE( sh.feature( buf ) == sh.feature( "abcde" ) );
}
TEST_CASE( "TireTree", "[Tree]" ) {
    TrieTree<char> ft;
    ft.insert( std::vector<char>( {'a', 'c', 'd'} ) );
    ft.insert( std::vector<char>( {'a', 'c', 'e', 'd'} ) );
    ft.insert( std::vector<char>( {'a', 'b', 'e', 'd'} ) );
    REQUIRE( ft.search( std::vector<char>( {'a', 'c', 'd'} ) ) );
    REQUIRE( !ft.search( std::vector<char>( {'a', 'd'} ) ) );
}
