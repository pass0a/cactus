#include "../kernels/operator.h"
#include "../kernels/eigenwrapper.h"

namespace cactus {
    class DotOp :public Operation {
    private:
        Tensor& x;
        Tensor& y;
    public:
        DotOp(Input _x, Input _y)
            :x(_x.node()->tensor()), y(_y.node()->tensor()) {
            inputs = { _x.node(),_y.node() };
        }

        template<typename ZT>
        void compute(Tensor& x, Tensor& y) {
            typename Matrix<ZT>::type ret, a, b;
            CASES(x.dtype(), a = Map<T>::mapping(x).cast<ZT>());
            CASES(y.dtype(), b = Map<T>::mapping(y).cast<ZT>());
            ret = a.array()*b.array();
            t = Tensor(ret.sum());
        }
        void compute() {
            int type = std::max(x.dtype(), y.dtype());
            assert(x.shape()==y.shape());
            CASES(type, compute<T>(x, y));
        }
    };
    Output dot(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<DotOp>(x, y));
    }
}
