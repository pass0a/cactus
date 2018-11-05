#include "../kernels/operator.h"
#include "../kernels/eigenwrapper.h"
namespace cactus {
    class PowOp :public Operation {
    private:
        Tensor& x;
        Tensor& y;
    public:
        PowOp(Input _x, Input _y)
            :x(_x.node()->tensor()), y(_y.node()->tensor()) {
            inputs = { _x.node(),_y.node() };
        }
        
        template<typename ZT>
        void compute() {
            Matrix<ZT>::type ret, a, b;
            CASES(x.dtype(), a = Map<T>::mapping(x).cast<ZT>());
            CASES(y.dtype(), b = Map<T>::mapping(y).cast<ZT>());
            if (x.shape() != y.shape()) {
                if (x.shape().total() == 1)
                {
                    ret = Eigen::pow(a(0, 0),b.array());
                }
                else if (y.shape().total() == 1) {

                    ret = Eigen::pow(a.array(),b(0, 0));
                }
                else {
                    assert(0);
                }
            }
            else {
                ret = Eigen::pow(a.array(),b.array());
            }
            t = Tensor(DataTypeToEnum<ZT>::value, { (std::size_t)ret.rows(),(std::size_t)ret.cols() });
            t.assign(ret.data(), ret.size() * sizeof(ZT));
        }
        void compute() {
            int type = std::max(x.dtype(), y.dtype());
            CASES(type, compute<T>());
        }
        template<typename T, typename T1, typename T2>
        void grad(xgrads& list, T1& a, T2& b) {
            typename Matrix<T>::type z = Eigen::pow(a, (b - 1))*(b);
            Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            Tensor dval = Tensor(DataTypeToEnum<T>::value, s);
            dval.assign(z.data(), z.size() * sizeof(T));
            list.push_back(std::make_pair(inputs[0], dval));

            auto v = wrap_log(a);

            z = Eigen::pow(a, b)*v;
            s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            dval = Tensor(DataTypeToEnum<T>::value, s);
            dval.assign(z.data(), z.size() * sizeof(T));
            list.push_back(std::make_pair(inputs[1], dval));
        }
        template<typename ZT>
        void grading(xgrads& list) {
            Matrix<ZT>::type ret, a, b;
            CASES(x.dtype(), a = Map<T>::mapping(x).cast<ZT>());
            CASES(y.dtype(), b = Map<T>::mapping(y).cast<ZT>());
            if (x.shape() != y.shape()) {
                if (x.shape().total() == 1)
                {
                    grad<ZT>(list,a(0, 0), (Array<ZT>::type)b.array());
                }
                else if (y.shape().total() == 1) {

                    grad<ZT>(list, (Array<ZT>::type)a.array(), b(0, 0));
                }
                else {
                    assert(0);
                }
            }
            else {
                grad<ZT>(list, (Array<ZT>::type)a.array(), (Array<ZT>::type)b.array());
            }
        }
        xgrads grad(Tensor& dval) {
            xgrads list;
            int type = std::max(x.dtype(), y.dtype());
            CASES(type, grading<T>(list));
            //ArrayCase(x, y, grad<T>(list, a, b));
            return list;
        }
    };
    Output pow(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<PowOp>(x, y));
    }
}
