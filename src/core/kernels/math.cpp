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
            auto xt = Map<T>::mapping(a);
            auto yt = Map<T>::mapping(b);
            typename Matrix<T>::type z = xt * yt;

            Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            t = Tensor(DataTypeToEnum<T>::value, s);
            t.assgin(z.data(), z.size() * sizeof(T));
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
            auto xt = Map<T>::mapping(a);
            auto yt = Map<T>::mapping(b);
            typename Matrix<T>::type z = xt+yt;
            
            Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            t= Tensor(DataTypeToEnum<T>::value, s);
            t.assgin(z.data(), z.size() * sizeof(T));
        }
        void compute() {
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();
            assert((x.shape() == y.shape()) && (x.dtype() == y.dtype()));
            CASES(x.dtype(),compute<T>(x,y) );
        }
    };
    Output matmul(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<MatMulOp>(x, y));
    }
    Output Add(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<AddOp>(x,y));
    }
}
