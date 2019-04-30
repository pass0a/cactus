#include "tree.hpp"
#include <algorithm>
#include <iostream>

template <typename T> class TrieTree {
  public:
    TrieTree()
        : root( 0 ) {}
    class find_func {
      public:
        find_func( TreeNode<T> v )
            : value( v ) {}
        bool operator()( TreeNode<T> node ) {
            return node.value == value.value;
        }

      private:
        TreeNode<T> value;
    };
    template <typename Container> void insert( Container data ) {
        auto p = &root;
        for ( auto x : data ) {
            auto it = std::find_if( p->children.begin(), p->children.end(),
                                    find_func( x ) );
            if ( it == p->children.end() ) {
                p->add( x );
                it = std::find_if( p->children.begin(), p->children.end(),
                                   find_func( x ) );
            }
            p = &( *it );
        }
    }
    template <typename Container> bool search( Container data ) {
        if ( data.size() == 0 ) return false;
        auto p = &root;
        for ( auto x : data ) {
            auto it = std::find_if( p->children.begin(), p->children.end(),
                                    find_func( x ) );
            if ( it == p->children.end() ) {
                return false;
            }
            p = &( *it );
        }
        //判断是否有以当前节点为结尾的字符串
        return true;
    }
    template <typename Container> bool remove( Container data ) {
        if ( data.size() == 0 ) return false;
        auto p = &root;
        for ( auto x : data ) {
            auto it = std::find_if( p->children.begin(), p->children.end(),
                                    find_func( x ) );
            if ( it == p->children.end() ) {
                return false;
            }
            p = &( *it );
        }
        //判断是否有以当前节点为结尾的字符串
        return true;
    }
    void dump() {
        std::stack<TreeNode<T>>  stack;
        std::vector<TreeNode<T>> result;
        stack.push( root );
        while ( stack.size() ) {
            auto top = stack.top();
            stack.pop();
            if ( result.size() > top.level ) {
                result.erase( result.begin() + top.level, result.end() );
            }
            result.push_back( top );
            auto children = top.children;
            if ( children.size() ) {
                for ( auto it = children.rbegin(); it != children.rend();
                      it++ ) {
                    stack.push( *it );
                }
            } else {
                for ( auto it = result.begin() + 1; it != result.end(); it++ ) {
                    std::cout << it->value;
                }
                std::cout << std::endl;
            }
        }
    }

  private:
    TreeNode<T> root;
};
