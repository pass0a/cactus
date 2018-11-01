/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_MATRIX_HPP_
#define SRC_MATRIX_HPP_

#include "../framework/tensor.hpp"
#include "../framework/node.hpp"
#include "../framework/graph.hpp"
#include "compute.h"
namespace cactus {
    class ProductOp :public Operation {
    public:
        ProductOp(Input& x, Input& y) {
            inputs = { x.node(),y.node() };
        }
        void compute() {
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();
            t= product_impl(x,y);
            
        }
    };
    class DotOp :public Operation {
    public:
        DotOp(Input& x, Input& y) {
            inputs = { x.node(),y.node() };
        }
        void compute() {
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();
            assert((x.shape() == y.shape()) && (x.dtype() == y.dtype()));
            t = dot_impl(x, y);

        }
    };
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
            assert((x.shape().cols == x.shape().rows) && (x.shape() == y.shape()) && (x.dtype() == y.dtype()));
            CASES(x.dtype(), compute<T>(x, y));
        }
    };
    class AddOp :public Operation {
    public:
        AddOp(Input& x, Input& y) {
            inputs = { x.node(),y.node() };
        }
        void compute() {
            t = add_impl(inputs[0]->tensor(), inputs[1]->tensor());
            
        }
    };
    class SubOp :public Operation {
    public:
        SubOp(Input& x, Input& y) {
            inputs = { x.node(),y.node() };
        }
        void compute() {
            t = sub_impl(inputs[0]->tensor(), inputs[1]->tensor());

        }
    };
    class SumOp :public Operation {
    public:
        SumOp(Input& x) {
            inputs = { x.node() };
        }
        void compute() {
            t = sum_impl(inputs[0]->tensor());
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
        xgrads grad(Tensor& dval) {
            xgrads list;
            auto x = inputs[0]->tensor();
            auto y = inputs[1]->tensor();

            ArrayCase(x, y, grad<T>(list, a, b));
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
    Output dot(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<DotOp>(x, y));
    }
    Output sum(Graph & g, Input x)
    {
        return g.insert(std::make_shared<SumOp>(x));
    }
    Output add(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<AddOp>(x, y));
    }
    Output sub(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<SubOp>(x, y));
    }
    Output product(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<ProductOp>(x, y));
    }
    Output pow(Graph & g, Input x, Input y)
    {
        return g.insert(std::make_shared<PowOp>(x, y));
    }
    Output assign(Graph & g, Input x, Input y) {
        return g.insert(std::make_shared<AssignOp>(x, y));
    }
}

#endif  // SRC_MATRIX_HPP_
