#include "../kernels/operator.h"
#include "../kernels/eigenwrapper.h"
namespace cactus {
    class ProductOp :public Operation {
    private:
        Tensor& x;
        Tensor& y;
    public:
        ProductOp(Input _x, Input _y)
            :x(_x.node()->tensor()), y(_y.node()->tensor()) {
            inputs = { _x.node(),_y.node() };
        }

        template<typename ZT>
        void compute(Tensor& x, Tensor& y) {
            Matrix<ZT>::type ret, a, b;
            CASES(x.dtype(), a = Map<T>::mapping(x).cast<ZT>());
            CASES(y.dtype(), b = Map<T>::mapping(y).cast<ZT>());
            if (x.shape() != y.shape()) {
                if (x.shape().total() == 1)
                {
                    ret = a(0, 0)*b.array();
                }
                else if (y.shape().total() == 1) {

                    ret = a.array()*b(0, 0);
                }
                else {
                    assert(0);
                }
            }
            else {
                ret = a.array()*b.array();
            }
            t = Tensor(DataTypeToEnum<ZT>::value, { (std::size_t)ret.rows(),(std::size_t)ret.cols() });
            t.assign(ret.data(), ret.size() * sizeof(ZT));
        }
        void compute() {
            int type = std::max(x.dtype(), y.dtype());
            CASES(type, compute<T>(x, y));
        }
    };
    Output product(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<ProductOp>(x, y));
    }
}
