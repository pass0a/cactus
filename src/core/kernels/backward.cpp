#include "backward.h"
#include <queue>
namespace cactus {
    BackwardOp::BackwardOp(Input& x) {
        inputs = { x.node() };
    }
    void BackwardOp::compute() {
        Node* parent = inputs[0],*child;
        std::queue<Node*> list;
        list.push(parent);
        
        while (!list.empty()) {
            parent=list.front();
            auto it = xr.insert(std::make_pair(parent, Xgrad(parent)));
            
            list.pop();
            for (int i = 0; i < parent->num_inputs(); i++) {
                child =child->input(i);
                child->grad();
                list.push(child);
            }
        }
        
        t = 1;
    }
    Output backward(Graph & g, Input x) {
        return g.insert(std::make_shared<BackwardOp>(x));
    }
}
