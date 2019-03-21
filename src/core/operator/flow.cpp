#include "../kernels/operator.h"
#include "../kernels/eigenwrapper.h"

namespace cactus {
    class CondOp :public Operation {
    public:
        CondOp(Input& cond,Input& x, Input& y) {
            inputs = { cond.node(),x.node(),y.node() };
        }
        void compute() {
            auto& cond = inputs[0]->tensor();
            auto& x = inputs[1]->tensor();
            auto& y = inputs[2]->tensor();
            if (cond.get<int>(0)) {
                t = x;
            }
            else {
                t = y;
            }
        }
    };
    Output cond(Graph & g, Input cond, Input x, Input y) {
        return g.insert(std::make_shared<CondOp>(cond,x, y));
    }
}
