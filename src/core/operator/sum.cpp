#include "../kernels/operator.h"
#include "../kernels/eigenwrapper.h"
namespace cactus {
    class SumOp :public Operation {
    private:
        Tensor& x;
    public:
        SumOp(Input _x)
            :x(_x.node()->tensor()) {
            inputs = { _x.node() };
        }

        template<typename T>
        void compute(Tensor& x) {
            Matrix<T>::type ret = Map<T>::mapping(x);
            t = Tensor(ret.sum());
        }
        void compute() {
            CASES(x.dtype(), compute<T>(x));
        }
    };
    Output sum(Graph & g, Input x)
    {
        return g.insert(std::make_shared<SumOp>(x));
    }
}
