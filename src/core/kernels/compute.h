
#ifndef SRC_OP_ADD_HPP_
#define SRC_OP_ADD_HPP_

#include "../framework/tensor.hpp"
#include "../framework/node.hpp"
#include "eigenwrapper.h"

namespace cactus {
    template<typename T, typename T1, typename T2>
    void product(Tensor& t, T1& a, T2& b) {
        typename Matrix<T>::type z = a * b;
        Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
        t = Tensor(DataTypeToEnum<T>::value, s);
        t.assign(z.data(), z.size() * sizeof(T));
    }
    Tensor product_impl(Tensor& x, Tensor& y) {
        Tensor t;
        TensorCase(x, y, product<T>(t, a, b));
        return t;
    }
    template<typename T, typename T1, typename T2>
    void dot(Tensor& t, T1& a, T2& b) {
        typename Matrix<T>::type z = a * b;
        t = Tensor(z.sum());
    }
    Tensor dot_impl(Tensor& x, Tensor& y) {
        Tensor t;
        ArrayCase(x, y, dot<T>(t, a, b));
        return t;
    }
    template<typename T, typename T1, typename T2>
    void add(Tensor& t, T1& a, T2& b) {
        typename Matrix<T>::type z = a+b;
        Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
        t = Tensor(DataTypeToEnum<T>::value, s);
        t.assign(z.data(), z.size() * sizeof(T));
    }
    Tensor add_impl(Tensor& x, Tensor& y) {
        Tensor t;
        ArrayCase(x,y, add<T>(t, a, b));
        return t;
    }
    template<typename T, typename T1, typename T2>
    void sub(Tensor& t, T1& a, T2& b) {
        typename Matrix<T>::type z = a-b;
        Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
        t = Tensor(DataTypeToEnum<T>::value, s);
        t.assign(z.data(), z.size() * sizeof(T));
    }
    Tensor sub_impl(Tensor& x, Tensor& y) {
        Tensor t;
        ArrayCase(x,y, sub<T>(t, a, b));
        return t;
    }
    template<typename T, typename T1, typename T2>
    void pow(Tensor& t, T1& a, T2& b) {
        typename Matrix<T>::type z = Eigen::pow(a, b);

        Shape s = { (std::size_t)z.rows(),(std::size_t)z.cols() };
        t = Tensor(DataTypeToEnum<T>::value, s);
        t.assign(z.data(), z.size() * sizeof(T));
    }
    Tensor pow_impl(Tensor& x, Tensor& y) {
        Tensor t;
        ArrayCase(x, y, pow<T>(t, a, b));
        return t;
    }
    template<typename T>
    void sum_impl(Tensor& t, Tensor& a) {
        auto xt = Map<T>::mapping(a);
        t = Tensor(xt.sum());
    }
    Tensor sum_impl(Tensor & x)
    {
        Tensor t;
        CASES(x.dtype(), sum_impl<T>(t, x));
        return t;
    }
}

#endif  // SRC_OP_ADD_HPP_