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
        template<typename T>
        void compute(Tensor& a,Tensor& b) {
            auto xt = Map<T>::mapping(a);
            auto yt = Map<T>::mapping(b);
            typename Matrix<T>::type z = xt+yt;
            
            Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            t= Tensor(DataTypeToEnum<T>::value, s);
            t.assign(z.data(), z.size() * sizeof(T));
        }
        void compute() {
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();
            /*std::cout<<x.dtype()<<":"<<y.dtype()<<std::endl;
            std::cout<<x.shape().rows<<":"<<y.shape().rows<<std::endl;*/
            assert((x.shape() == y.shape()) && (x.dtype() == y.dtype()));
            CASES(x.dtype(),compute<T>(x,y) );
        }
    };
    class PowOp :public Operation {
    public:
        PowOp(Input& x, Input& y) {
            inputs = { x.node(),y.node() };
        }
        template<typename T>
        void compute(Tensor& a, Tensor& b) {
            auto xt = Map<T>::mapping(a);
            auto yt = Map<T>::mapping(b);
            typename Matrix<T>::type z;
            if (a.shape().total == 1 && b.shape().total()==1) {
                z = Eigen::pow(xt.array(), yt.array());
            }
            
            
            Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            t = Tensor(DataTypeToEnum<T>::value, s);
            t.assign(z.data(), z.size() * sizeof(T));
        }
        void compute() {
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();
            
            std::cout<<x.dtype()<<":"<<y.dtype()<<std::endl;
            
            assert(/*(x.shape() == y.shape()) &&*/ (x.dtype() == y.dtype()));
            CASES(x.dtype(), compute<T>(x, y));
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
    class BackwardOp :public Operation {
    public:
        BackwardOp(Input& x) {
            inputs = { x.node()};
        }
        void compute() {
            auto& x = inputs[0];
            t = x->tensor();
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
    Output backward(Graph & g, Input x)
    {
        return g.insert(std::make_shared<BackwardOp>(x));
    }
}
