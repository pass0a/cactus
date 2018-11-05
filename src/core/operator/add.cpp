#include "../kernels/operator.h"
#include "../kernels/eigenwrapper.h"
namespace cactus {
    
    class AddOp :public Operation {
    private:
        Tensor& x;
        Tensor& y;
    public:
        AddOp(Input _x, Input _y)
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
                    ret = a(0, 0)+b.array();
                }
                else if (y.shape().total() == 1) {

                    ret = a.array()+b(0, 0);
                }
                else {
                    assert(0);
                }
            }
            else {
                ret = a.array()+b.array();
            }
            t = Tensor(DataTypeToEnum<ZT>::value, { (std::size_t)ret.rows(),(std::size_t)ret.cols() });
            t.assign(ret.data(), ret.size() * sizeof(ZT));
        }
        void compute() {
            int type = std::max(x.dtype(), y.dtype());
            CASES(type, compute<T>(x, y));
        }
    };
    Output add(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<AddOp>(x, y));
    }
    Tensor add_impl(Tensor& x, Tensor& y) {
        NodeConst a(x), b(y);
        Output pa(&a),pb(&b);
        AddOp op(pa,pb);
        op.compute();
        return op.tensor();
    }
}
