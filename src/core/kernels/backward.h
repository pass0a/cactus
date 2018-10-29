#include "framework\node.hpp"
#include "framework\graph.hpp"

namespace cactus {
    class Xgrad {
    public:
        Xgrad(Node* p) :ptr(p) {
        }
        void grad(Tensor val) {
            dval = val;
        }
    private:
        Node* ptr;
        Tensor dval;
        Tensor dxval;
    };
    class BackwardOp :public Operation {
    public:
        BackwardOp(Input& x);
        void compute();
    private:
        std::map<Node*,Xgrad> xr;
    };
    Output backward(Graph & g, Input x);
    
}
