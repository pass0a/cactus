
#ifndef SRC_OP_ADD_HPP_
#define SRC_OP_ADD_HPP_

#include "../framework/tensor.hpp"
#include "../framework/node.hpp"
#include "eigenwrapper.h"

namespace cactus {
    Tensor add(Tensor& x, Tensor& y);
}

#endif  // SRC_OP_ADD_HPP_