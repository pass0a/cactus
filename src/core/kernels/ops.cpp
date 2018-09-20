#include "ops.hpp"
namespace cactus {
    Output Const(Graph& g, const Input::Initializer& v) {
        return g.insert(std::make_shared<NodeConst>(v.tensor));
    }
    Output Variable(Graph& g, const Shape s,DataType dt) {
        return g.insert(std::make_shared<NodeVariable>(s,dt));
    }
    Output Placeholder(Graph& g, DataType dt, Shape s) {
        return g.insert(std::make_shared<NodePlaceholder>(s,dt));
    }
}