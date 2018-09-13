/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_GRAPH_HPP_
#define SRC_GRAPH_HPP_

#include <string>
#include <vector>
#include <utility>

#include "variables.hpp"
#include "tensor.hpp"
#include "operation.hpp"

namespace cactus {

    class graph {
    public:
        Tensor insert(const Tensor& v) {
            return v;
        }
    private:
        std::vector<operation> list;
    };
}

#endif  // SRC_GRAPH_HPP_
