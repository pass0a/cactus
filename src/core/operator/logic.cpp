#include "../kernels/operator.h"
#include "../kernels/eigenwrapper.h"

namespace cactus {

    class LessOp :public Operation {
    private:
        Tensor& x, &y;
        int mothed;
    public:
        LessOp(Input& _x, Input& _y,int _mothed) 
            :x(_x.node()->tensor()), y(_y.node()->tensor()),mothed(_mothed) {
            inputs = { _x.node(),_y.node() };
        }
        template<typename ZT>
        void compute() {
            typename Matrix<ZT>::type a, b;
            typename Matrix<bool>::type ret;
            typename Matrix<int>::type rs;
            CASES(x.dtype(), a = Map<T>::mapping(x).cast<ZT>());
            CASES(y.dtype(), b = Map<T>::mapping(y).cast<ZT>());
            if (x.shape() != y.shape()) {
                if (y.shape().total() == 1) {
                    switch (mothed)
                    {
                    case 0:
                        ret = (a.array()<b(0, 0));
                        break;
                    case 1:
                        ret = (a.array()>b(0, 0));
                        break;
                    case 2:
                        ret = (a.array()<=b(0, 0));
                        break;
                    case 3:
                        ret = (a.array() >= b(0, 0));
                        break;
                    case 4:
                        ret = (a.array() == b(0, 0));
                        break;
                    case 5:
                        ret = (a.array() != b(0, 0));
                        break;
                    default:
                        assert(0);
                        break;
                    }
                    
                }
                else {
                    assert(0);
                }
            }
            else {
                switch (mothed)
                {
                case 0:
                    ret = (a.array()<b.array());
                    break;
                case 1:
                    ret = (a.array()>b.array());
                    break;
                case 2:
                    ret = (a.array() <= b.array());
                    break;
                case 3:
                    ret = (a.array() >= b.array());
                    break;
                case 4:
                    ret = (a.array() == b.array());
                    break;
                case 5:
                    ret = (a.array() != b.array());
                    break;
                default:
                    assert(0);
                    break;
                }
            }
            rs = ret.cast<int>();
            t = Tensor(DataTypeToEnum<int>::value, { (std::size_t)rs.rows(),(std::size_t)rs.cols() });
            t.assign(rs.data(), rs.size() * sizeof(int));
        }
        void compute() {
            
            int type = std::max(x.dtype(), y.dtype());
            CASES(type, compute<T>());
        }
    };
    
    Output lt(Graph & g,Input x, Input y) {
        return g.insert(std::make_shared<LessOp>(x, y,0));
    }
    Output gt(Graph & g, Input x, Input y) {
        return g.insert(std::make_shared<LessOp>(x, y, 1));
    }
    Output ltoe(Graph & g, Input x, Input y) {
        return g.insert(std::make_shared<LessOp>(x, y, 2));
    }
    Output gtoe(Graph & g, Input x, Input y) {
        return g.insert(std::make_shared<LessOp>(x, y, 3));
    }
    Output eq(Graph & g, Input x, Input y) {
        return g.insert(std::make_shared<LessOp>(x, y, 4));
    }
    Output neq(Graph & g, Input x, Input y) {
        return g.insert(std::make_shared<LessOp>(x, y, 5));
    }
}
