#include "matrix.h"
#include "operation.hpp"

namespace cactus {
    template<typename T>
    class base_matmul:public operation {
    public:
        base_matmul() {}
        void input(std::vector<Tensor> args) {
            list = args;
        }
        Tensor compute() {
            Tensor& a = list[0];
            Tensor& b = list[1];
            Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> x((T*)a.data(), a.shape().rows, a.shape().cols);
            Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> y((T*)b.data(), b.shape().rows, b.shape().cols);
            Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> z = x*y;
            Shape s = { (uint32_t)z.rows(),(uint32_t)z.cols() };
            Tensor c(DataTypeToEnum<T>::value, s);
            std::memcpy(c.data(),
                z.data(),
                c.TotalBytes());
            return c;
        }
        std::vector<Tensor> list;
    };

    Tensor matmul(Tensor a, Tensor b) {
        std::shared_ptr<operation> f;
        CASES(a.dtype(), f = std::shared_ptr<operation>(new base_matmul<T>()));
        f->input({ a,b });
        return f->compute();
    }
}