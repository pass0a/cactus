/*
    Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_OPS_HPP_
#define SRC_OPS_HPP_

#include "../framework/node.hpp"
#include "../framework/graph.hpp"


namespace cactus {
    Output Const(Graph& g, const Input::Initializer& v) {
        return g.insert(std::make_shared<NodeConst>(v.tensor));
    }
    Output Variable(Graph& g, const Input::Initializer& v) {
        return g.insert(std::make_shared<NodeVariable>(v.tensor));
    }
    Output Placeholder(Graph& g, DataType dt, Shape s = { 1,1 }) {
        return g.insert(std::make_shared<NodePlaceholder>(s, dt));
    }
}  // namespace cactus

#endif  // SRC_OPS_HPP_
