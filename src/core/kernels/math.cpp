#include "math.h"
#include "../framework/operation.hpp"
#include "compute.h"
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
            t.assign(z.data(), z.size() * sizeof(T));
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
        void compute() {
            t=add_impl(inputs[0]->tensor(), inputs[1]->tensor());
        }
    };
    class PowOp :public Operation {
    public:
        PowOp(Input& x, Input& y) {
            inputs = { x.node(),y.node() };
        }
        void compute() {
            t = pow_impl(inputs[0]->tensor(), inputs[1]->tensor());
        }
        template<typename T,typename T1,typename T2>
        void grad(xgrads& list,T1& a, T2& b) {
            typename Matrix<T>::type z=Eigen::pow(a,(b-1))*(b);
            Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            Tensor dval = Tensor(DataTypeToEnum<T>::value, s);
            dval.assign(z.data(), z.size() * sizeof(T));
            list.push_back(std::make_pair(inputs[0],dval));

            z = Eigen::pow(a, b)*wrap_log(a);
            s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            dval=Tensor(DataTypeToEnum<T>::value, s);
            dval.assign(z.data(), z.size() * sizeof(T));
            list.push_back(std::make_pair(inputs[1],dval));
        }
        xgrads grad(Tensor& dval) {
            xgrads list;
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();

            ArrayCase(x,y, grad<T>(list,a, b));
            return list;
        }
    };
    class AssignOp :public Operation {
    public:
        AssignOp(Input& x, Input& y) {
            inputs = { x.node(),y.node() };
        }
        void compute() {
            auto& x = inputs[0]->tensor();
            auto& y = inputs[1]->tensor();
            assert((x.shape() == y.shape()) && (x.dtype() == y.dtype()));
            x.assign(y);
            t = x;
        }
    };
    
    Output matmul(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<MatMulOp>(x, y));
    }
    Output add(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<AddOp>(x,y));
    }
    Output pow(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<PowOp>(x, y));
    }
    Output assign(Graph & g, Input x, Input y) {
        return g.insert(std::make_shared<AssignOp>(x, y));
    }
    
}
