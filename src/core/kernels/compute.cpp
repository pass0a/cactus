
#include "compute.h"


namespace cactus {
    template<typename T>
    void add(Tensor& t, Tensor& a, Tensor& b) {
        auto xt = Map<T>::mapping(a);
        auto yt = Map<T>::mapping(b);
        typename Matrix<T>::type z = xt + yt;

        Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
        t = Tensor(DataTypeToEnum<T>::value, s);
        t.assign(z.data(), z.size() * sizeof(T));
    }
    
    Tensor add(Tensor& x, Tensor& y) {
        Tensor t;
        assert((x.shape() == y.shape()) && (x.dtype() == y.dtype()));
        CASES(x.dtype(), add<T>(t, x, y));
        return t;
    }
}
