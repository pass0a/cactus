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
            t=add(inputs[0]->tensor(), inputs[1]->tensor());
        }
    };
    class PowOp :public Operation {
    public:
        PowOp(Input& x, Input& y) {
            inputs = { x.node(),y.node() };
        }
        template<typename T>
        void compute(Tensor& a, Tensor& b) {
            
            typename Matrix<T>::type z;
            
            if (a.shape() != b.shape()) {
                if (x.shape().total() == 1) {
                    auto yt = Map<T>::mapping(b);
                    z = Eigen::pow(a.get<T>(0), yt);
                }
                else if (y.shape().total() == 1) {
                    auto xt = Map<T>::mapping(a);
                    z = Eigen::pow(xt, b.get<T>());
                }
                else {
                    assert(a.shape()==b.shape());
                }
            }
            else {
                auto xt = Map<T>::mapping(a);
                auto yt = Map<T>::mapping(b);
                z = Eigen::pow(xt,yt);
            }
            Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            t = Tensor(DataTypeToEnum<T>::value, s);
            t.assign(z.data(), z.size() * sizeof(T));
        }
        void compute() {
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();
            
            CASES(x.dtype(), compute<T>(x, y));
        }
        template<typename T>
        void grad(xgrads& list,Tensor& a, Tensor& b) {
            
            auto xt = Map<T>::mapping(a);
            auto yt = Map<T>::mapping(b);
            typename Matrix<T>::type z;

            yt.array() -= 1;
            if (a.shape().total() == 1 && b.shape().total() != 1) {
                z = Eigen::pow(a.get<T>(0), yt.array())*yt.array();
            }
            else if (a.shape().total() != 1 && b.shape().total() == 1) {
                z = Eigen::pow(xt.array(), b.get<T>(0));
            }
            else {
                z = Eigen::pow(xt.array(), yt.array());
            }
            Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
            Tensor dval = Tensor(DataTypeToEnum<T>::value, s);
            dval.assign(z.data(), z.size() * sizeof(T));
            std::cout << z << std::endl;
            std::cout << yt << std::endl;
            list.push_back(std::make_pair(inputs[0],dval));
        }
        xgrads grad(Tensor& dval) {
            xgrads list;
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();

            assert((x.shape() == y.shape() || x.shape().total() == 1 || y.shape().total() == 1) && (x.dtype() == y.dtype()));
            CASES(x.dtype(), grad<T>(list,x, y));
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
