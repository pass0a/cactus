/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_GRAPH_HPP_
#define SRC_GRAPH_HPP_

#include <string>
#include <vector>
#include <deque>
#include <map>
#include <iostream>
#include <utility>
#include "node.hpp"

namespace cactus {

    class Graph {
    private:
        void compute() {
            for (auto v:needcompute)
            {
                switch (v->type()) {
                case NtOperation:
                    ((Operation*)v)->compute();
                    break;
                default:
                    break;
                }
            }
        }
        void computeQueue(Output& out) {
            Node* root = out.node();
            std::size_t nums = 0;
            std::deque<std::pair<Node*, std::size_t>> tmp;
            tmp.push_back(std::make_pair(root, 0));
            while (!tmp.empty())
            {
                root = tmp.back().first;
                nums = root->num_inputs();
                if (root == NULL)
                    continue;
                if (!tmp.back().second) {
                    tmp.back().second = 1;
                    for (size_t i = 0; i < nums; i++)
                    {
                        tmp.push_back(std::make_pair(root->input(nums - i - 1), 0));
                    }
                }
                else {
                    if (root->status() == CtNoCompute) {
                        root->status(CtQueuing);
                        needcompute.push_back(root);
                    }
                    tmp.pop_back();
                }
            }
        }
    public:
        Graph& opName(std::string name) {
            op_named = name;
            return *this;
        }
        void run(Output& out) {
            computeQueue(out);
            compute();
            return;
        }
        Output insert(const std::shared_ptr<Node> nptr) {
            if (op_named.size()) {
                nptr->name(op_named);
                named.insert(std::pair<std::string, std::shared_ptr<Node>>(op_named, nptr));
                op_named = "";
            }
            else {
                unamed.push_back(nptr);
            }
            return Output(nptr.get());
        }
    private:
        std::map<std::string,std::shared_ptr<Node>> named;
        std::vector<std::shared_ptr<Node>> unamed;
        std::deque<Node*> needcompute;
        std::string op_named;
    };
}

#endif  // SRC_GRAPH_HPP_
