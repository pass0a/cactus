#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
// template <typename T> class TrieTree {
//     class TrieNode {
//       public:
//         TrieNode( T v )
//             : value( v ) {}
//         std::vector<TrieNode> &children() { return child_; }
//         void add( TrieNode node ) { child_.emplace_back( node ); }
//         void del( TrieNode node ) {
//             auto it = std::find( child_.begin(), child_.end(), node );
//             child_.erase();
//         }

//       private:
//         T                     value;
//         std::vector<TrieNode> child_;
//     };

//   public:
//     template <typename container> void insert( container cc ) {
//         auto p = &root;
//         for ( auto x : cc ) {
//             auto obj = std::find( p->begin(), p->end(), x );
//             if ( std::end( *p ) == obj ) {
//                 root.emplace_back( TrieNode( x ) );
//                 obj = std::find( p->begin(), p->end(), x );
//             }
//             p = &( obj->children() );
//         }
//     }
//     void dump() {
//         std::vector<TrieNode> stack;
//         for ( auto n : root ) {
//             stack.emplace_back( n );
//             while ( stack.size() ) {
//                 for ( stack )
//             }
//         }
//     }

//   private:
//     std::vector<TrieNode> root;
// };
template <typename T> class TreeNode {
  public:
    T                     value;
    std::vector<TreeNode> children;

  public:
    TreeNode() {}
    TreeNode( T val )
        : value( val ) {}
    void add( const TreeNode node ) { children.emplace_back( node ); }
};
template <typename T> class Tree {
  public:
    void bfs( TreeNode<T> root ) {
        std::cout << root.value << std::endl;
        for ( auto x : root.children ) {
            std::cout << x.value << std::endl;
        }
    }
};

int main() {
    TreeNode<char> tmp( 'z' );
    TreeNode<char> v( 'b' );
    v.add( TreeNode<char>( 'c' ) );
    tmp.add( TreeNode<char>( 'd' ) );
    tmp.add( v );
    Tree<char> t;
    t.bfs( tmp );
    // TrieTree<float> floatset;
    // TrieTree<char>  charset;
    // floatset.insert<std::vector<float>>( {0, 1.2, 1.5, 16.5} );
    // charset.insert<std::string>( "123456789" );
    return 0;
}
