#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

template <typename T> class TreeNode {
  public:
    T                     value;
    std::vector<TreeNode> children;
    size_t                level;

  public:
    TreeNode()
        : level( 0 ) {}
    TreeNode( T val )
        : value( val )
        , level( 0 ) {}
    void add( TreeNode node ) {
        node.level = level + 1;
        children.emplace_back( node );
    }
};
template <typename T> class Tree {
  public:
    std::vector<TreeNode<T>> dfs( TreeNode<T> root ) {
        std::stack<TreeNode<T>>  stack;
        std::vector<TreeNode<T>> result;
        stack.push( root );
        while ( stack.size() ) {
            auto top = stack.top();
            stack.pop();
            result.push_back( top );
            auto children = top.children;
            if ( children.size() ) {
                for ( auto it = children.rbegin(); it != children.rend();
                      it++ ) {
                    stack.push( *it );
                }
            }
        }
        return result;
    }
    std::vector<TreeNode<T>> bfs( TreeNode<T> root ) {
        std::vector<TreeNode<T>> result;
        std::queue<TreeNode<T>>  queue;
        queue.push( root );
        while ( queue.size() ) {
            auto top = queue.front();
            queue.pop();
            result.push_back( top );
            auto children = top.children;
            if ( children.size() ) {
                for ( auto v : children ) {
                    queue.push( v );
                }
            }
        }
        return result;
    }
};
template <typename T> class TrieTree {
  public:
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
    template <typename Container>
    void insert( TreeNode<T> &root, Container data ) {
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
    template <typename Container>
    bool search( TreeNode<T> &root, Container data ) {
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
    template <typename Container>
    bool remove( TreeNode<T> &root, Container data ) {
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
    void dump( TreeNode<T> root ) {
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
};

int main() {
    TreeNode<char> tmp( 'a' );
    TreeNode<char> b( 'b' );
    TreeNode<char> c( 'c' );
    TreeNode<char> d( 'd' );
    b.add( c );
    d.add( TreeNode<char>( 'e' ) );
    tmp.add( b );
    tmp.add( d );
    Tree<char> t;
    auto       dfs = t.dfs( tmp );
    auto       bfs = t.bfs( tmp );

    for ( auto x : dfs ) {
        std::cout << x.value;
    }

    for ( auto x : bfs ) {
        std::cout << x.value;
    }
    std::cout << std::endl;
    TreeNode<char> ftroot( 0 );
    TrieTree<char> ft;
    ft.insert( ftroot, std::vector<char>( {'a', 'c', 'd'} ) );
    ft.insert( ftroot, std::vector<char>( {'a', 'c', 'e', 'd'} ) );
    ft.insert( ftroot, std::vector<char>( {'a', 'b', 'e', 'd'} ) );
    ft.dump( ftroot );
    std::cout << ft.search( ftroot, std::vector<char>( {'a', 'd'} ) );
    // TrieTree<float> floatset;
    // TrieTree<char>  charset;
    // floatset.insert<std::vector<float>>( {0, 1.2, 1.5, 16.5} );
    // charset.insert<std::string>( "123456789" );
    return 0;
}
