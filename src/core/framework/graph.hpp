/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_GRAPH_HPP_
#define SRC_GRAPH_HPP_

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "node.hpp"

namespace cactus {

    class Graph {
    public:
        void run(Output& out) {
            Node* result = out.node();
            switch (result->type())
            {
            case NtOperation:
                {
                    Operation* opt = (Operation*)result;
                    opt->compute();
                }
                break;
            default:
                break;
            }
            return;
        }
        const Output& insert(const std::shared_ptr<Node> nptr) {
            unamed.push_back(nptr);
            return Output(nptr.get());
        }
        const Output& insert(std::string name,const std::shared_ptr<Node> nptr) {
            named.insert(std::pair<std::string,std::shared_ptr<Node>>(name,nptr));
            return Output(nptr.get());
        }
    private:
        std::map<std::string,std::shared_ptr<Node>> named;
        std::vector<std::shared_ptr<Node>> unamed;
    };
}

#endif  // SRC_GRAPH_HPP_
