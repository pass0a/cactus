/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_MATRIX_HPP_
#define SRC_MATRIX_HPP_

#include "../framework/tensor.hpp"
#include <Eigen/Dense>
#include <vector>
#include "../framework/node.hpp"
#include "../framework/graph.hpp"
namespace cactus {
    Tensor matmul(Tensor a, Tensor b);
    const Output& Add(Graph& g, Input x, Input b);
}

#endif  // SRC_MATRIX_HPP_
