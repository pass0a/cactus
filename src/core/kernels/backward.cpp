#include "backward.h"
namespace cactus {
    BackwardOp::BackwardOp(Input& x) {
        inputs = { x.node() };
    }
    void BackwardOp::compute() {
        auto& root = inputs[0];
        //x.grad();

        //t = x->tensor();
    }
    Output backward(Graph & g, Input x) {
        return g.insert(std::make_shared<BackwardOp>(x));
    }
}
