/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_MATRIX_HPP_
#define SRC_MATRIX_HPP_

#include "../framework/graph.hpp"

namespace cactus {
    Output Cx_EXPORTS matmul(Graph & g, Input x, Input y);
    Output Cx_EXPORTS dot(Graph & g, Input x, Input y);
    Output Cx_EXPORTS sum(Graph & g, Input x);
    Output Cx_EXPORTS add(Graph & g, Input x, Input y);
    Output Cx_EXPORTS sub(Graph & g, Input x, Input y);
    Output Cx_EXPORTS product(Graph & g, Input x, Input y);
    Output Cx_EXPORTS pow(Graph & g, Input x, Input y);
    Output Cx_EXPORTS assign(Graph & g, Input x, Input y);

    Output Cx_EXPORTS cond(Graph & g, Input cond, Input x, Input y);
    Output Cx_EXPORTS lt(Graph & g, Input x, Input y);
    Output Cx_EXPORTS gt(Graph & g, Input x, Input y);
    Output Cx_EXPORTS ltoe(Graph & g, Input x, Input y);
    Output Cx_EXPORTS gtoe(Graph & g, Input x, Input y);
    Output Cx_EXPORTS eq(Graph & g, Input x, Input y);
    Output Cx_EXPORTS neq(Graph & g, Input x, Input y);
}

#endif  // SRC_MATRIX_HPP_
