/*
    Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_OPS_HPP_
#define SRC_OPS_HPP_

#include "../framework/node.hpp"
#include "../framework/graph.hpp"


namespace cactus {

const Output& Const(Graph& g,const Input::Initializer& v) {
    return g.insert(std::make_shared<NodeConst>(v.tensor));
}
const Output& Variable(Graph& g, const Input::Initializer& v) {
    return g.insert(std::make_shared<NodeConst>(v.tensor));
}
const Tensor Placeholder( DataType type, Shape s = {1,1}) {
    return Tensor(type, s);
}

}  // namespace cactus

#endif  // SRC_OPS_HPP_
