#include "../kernels/operator.h"
#include "../kernels/eigenwrapper.h"

namespace cactus {
    class MatMulOp :public Operation {
    private:
        Tensor& x;
        Tensor& y;
    public:
        MatMulOp(Input _x, Input _y)
            :x(_x.node()->tensor()), y(_y.node()->tensor()) {
            inputs = { _x.node(),_y.node() };
        }

        template<typename ZT>
        void compute(Tensor& x, Tensor& y) {
            Matrix<ZT>::type ret, a, b;
            CASES(x.dtype(), a = Map<T>::mapping(x).cast<ZT>());
            CASES(y.dtype(), b = Map<T>::mapping(y).cast<ZT>());
            ret = a*b;
            t = Tensor(DataTypeToEnum<ZT>::value, { (std::size_t)ret.rows(),(std::size_t)ret.cols() });
            t.assign(ret.data(), ret.size() * sizeof(ZT));
        }
        void compute() {
            int type = std::max(x.dtype(), y.dtype());
            assert(x.shape() == y.shape());
            CASES(type, compute<T>(x, y));
        }
    };
    Output matmul(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<MatMulOp>(x, y));
    }
}
