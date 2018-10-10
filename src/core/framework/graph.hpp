/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_GRAPH_HPP_
#define SRC_GRAPH_HPP_

#include "../kernels/ops_graph.h"
#include "node.hpp"
#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace cactus {

class Graph {
  private:
    void compute() {
        for (auto v : needcompute) {
            switch (v->type()) {
            case NtOperation:
                ((Operation *)v)->run();
                break;
            default:
                break;
            }
        }
        for (auto v : needcompute) {
            v->status(CtNoCompute);
        }
        needcompute.clear();
    }
    void computeQueue(Output &out) {
        Node *root = out.node();
        std::size_t nums = 0;
        std::deque<std::pair<Node *, std::size_t>> tmp;
        tmp.push_back(std::make_pair(root, 0));
        while (!tmp.empty()) {
            root = tmp.back().first;
            nums = root->num_inputs();
            if (root == NULL)
                continue;
            if (!tmp.back().second) {
                tmp.back().second = 1;
                for (size_t i = 0; i < nums; i++) {
                    tmp.push_back(std::make_pair(root->input(nums - i - 1), 0));
                }
            } else {
              if (root->status() == CtNoCompute && (root->type()==NtOperation)) {
                    root->status(CtQueuing);
                    needcompute.push_back(root);
                }
                tmp.pop_back();
            }
        }
    }

  public:
    Graph &opName(std::string name) {
        op_named = name;
        return *this;
    }
    void run(Output &out) {
        computeQueue(out);
        compute();
        return;
    }
    void run(Output &out, const std::initializer_list<std::pair<std::string,Input::Initializer>> &v) {
        std::map<std::string, Node *>::iterator it;
        for (auto n : v) {
            it=named.find(n.first);
            if (it != named.end()) {
                it->second->tensor().assign(n.second.tensor);
            }
        }
        computeQueue(out);
        compute();
        return;
    }
    Output insert(const std::shared_ptr<Node> nptr) {
        all.push_back(nptr);
        if (op_named.size()) {
            nptr->name(op_named);
            named.insert(std::pair<std::string, Node *>(op_named, nptr.get()));
            op_named = "";
        }
        if (nptr->type() == NtVariable) {
          variables.push_back(nptr.get());
        }
        return Output(nptr.get());
    }
    Output initAllVariable() {
        return insert(std::make_shared<InitVariable>(variables));
    }

  private:
    std::map<std::string, Node *> named;
    std::vector<std::shared_ptr<Node>> all;
    std::deque<Node *> needcompute;
    std::vector<Node *> variables;
    std::string op_named;
};
} // namespace cactus

#endif // SRC_GRAPH_HPP_
