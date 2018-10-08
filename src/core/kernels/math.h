/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_MATRIX_HPP_
#define SRC_MATRIX_HPP_

#include "../framework/tensor.hpp"
#include "../framework/node.hpp"
#include "../framework/graph.hpp"

namespace cactus {
    Output matmul(Graph& g, Input x, Input b);
    Output add(Graph& g, Input x, Input b);
    Output assign(Graph & g, Input x, Input y);
}

#endif  // SRC_MATRIX_HPP_
