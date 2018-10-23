#include "framework\node.hpp"
#include "framework\graph.hpp"

namespace cactus {
    class BackwardOp :public Operation {
    public:
        BackwardOp(Input& x);
        void compute();
    };
    Output backward(Graph & g, Input x);
    
}
