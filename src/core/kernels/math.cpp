#include "math.h"
#include "eigenwrapper.h"
#include "../framework/operation.hpp"
#include <cassert>
#include <vector>

namespace cactus {
    class MatMulOp :public Operation {
    public:
        MatMulOp(Input& x, Input& y) {
            inputs = { x.node(),y.node() };
        }
        template<typename T>
        void compute(Tensor& a, Tensor& b) {
            Map<T>::type xt((T*)a.data(), a.shape().rows, a.shape().cols);
            Map<T>::type yt((T*)b.data(), b.shape().rows, b.shape().cols);
            Matrix<T>::type z = xt * yt;

            Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            t = Tensor(DataTypeToEnum<T>::value, s);
            std::memcpy(t.data(), z.data(), t.TotalBytes());
        }
        void compute() {
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();
            assert((x.shape() == y.shape()) && (x.dtype() == y.dtype()));
            CASES(x.dtype(), compute<T>(x, y));
        }
    };
    class AddOp :public Operation {
    public:
        AddOp(Input& x,Input& y) {
            inputs = {x.node(),y.node()};
        }
        template<typename T>
        void compute(Tensor& a,Tensor& b) {
            Map<T>::type xt((T*)a.data(), a.shape().rows, a.shape().cols);
            Map<T>::type yt((T*)b.data(), b.shape().rows, b.shape().cols);
            Matrix<T>::type z = xt+yt;
            
            Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            t= Tensor(DataTypeToEnum<T>::value, s);
            std::memcpy(t.data(), z.data(), t.TotalBytes());
        }
        void compute() {
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();
            assert((x.shape() == y.shape()) && (x.dtype() == y.dtype()));
            CASES(x.dtype(),compute<T>(x,y) );
        }
    };
    Output matmul(Graph & g, Input x, Input b)
    {
        return g.insert(std::make_shared<MatMulOp>(x, b));
    }
    Output Add(Graph & g, Input x, Input b)
    {
        return g.insert(std::make_shared<AddOp>(x,b));
    }
}
