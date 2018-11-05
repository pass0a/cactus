#include "../kernels/operator.h"
#include "../kernels/eigenwrapper.h"

namespace cactus {
    class AssignOp :public Operation {
    public:
        AssignOp(Input& x, Input& y) {
            inputs = { x.node(),y.node() };
        }
        void compute() {
            auto& x = inputs[0]->tensor();
            auto& y = inputs[1]->tensor();
            assert((x.shape() == y.shape()) && (x.dtype() == y.dtype()));
            x.assign(y);
            t = x;
        }
    };
    Output assign(Graph & g, Input x, Input y) {
        return g.insert(std::make_shared<AssignOp>(x, y));
    }
}
