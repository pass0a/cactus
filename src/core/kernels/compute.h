
#ifndef SRC_OP_ADD_HPP_
#define SRC_OP_ADD_HPP_

#include "../framework/tensor.hpp"

namespace cactus{
    Tensor add_impl(Tensor& x, Tensor& y);
    Tensor sub_impl(Tensor& x, Tensor& y);
    Tensor product_impl(Tensor& x, Tensor& y);
    Tensor sum_impl(Tensor & x);
    Tensor pow_impl(Tensor& x, Tensor& y);
    Tensor dot_impl(Tensor& x, Tensor& y);
}

#endif  // SRC_OP_ADD_HPP_