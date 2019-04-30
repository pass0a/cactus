#include <queue>
#include <stack>
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
