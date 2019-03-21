/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_GRAPH_HPP_
#define SRC_GRAPH_HPP_

#include "node.hpp"
#include <memory>

namespace cactus {

    class Cx_EXPORTS Graph {
    public:
        Graph &opName(std::string name);
        void run(Output out);
        void run(Output out, const std::initializer_list<std::pair<std::string, Initializer>> &v);
        Output insert(const std::shared_ptr<Node> nptr);
        Output initAllVariable();
        Graph();
    private:
        class GraphImpl* impl;
    };
} // namespace cactus

#endif // SRC_GRAPH_HPP_
