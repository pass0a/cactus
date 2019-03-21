/*
    Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_OPS_HPP_
#define SRC_OPS_HPP_

#include "../framework/graph.hpp"

namespace cactus {
    Output Cx_EXPORTS Const(Graph& g, const Initializer& v);
    Output Cx_EXPORTS Variable(Graph& g, const Initializer& v);
    Output Cx_EXPORTS Placeholder(Graph& g, DataType dt, Shape s = { 1,1 });
    Output Cx_EXPORTS Random(Graph& g, DataType dt, Shape s = { 1,1 });
}  // namespace cactus

#endif  // SRC_OPS_HPP_
