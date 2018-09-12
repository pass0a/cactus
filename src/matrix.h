/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_MATRIX_HPP_
#define SRC_MATRIX_HPP_

#include "tensor.hpp"
#include <Eigen/Dense>
#include <vector>

namespace cactus {
    Tensor matmul(Tensor a, Tensor b);
}

#endif  // SRC_MATRIX_HPP_
