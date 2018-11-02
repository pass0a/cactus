#include "graph.hpp"
#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>


namespace cactus {
    class InitVariable : public Operation {
    public:
        InitVariable(std::vector<Node *> l) { inputs = l; }
        void compute() {
            for (auto n : inputs) {
                switch (n->type()) {
                case NtVariable:
                    n->compute();
                    break;
                default:
                    break;
                }
            }
        }
        NodeType type() { return NtInitOp; }
    };
    class GraphImpl {
    private:
        void compute() {
            for (auto v : needcompute) {
                switch (v->type()) {
                case NtOperation:
                case NtInitOp:
                case NtGradOp:
                    ((Operation *)v)->run();
                    break;
                default:
                    break;
                }
            }
            for (auto v : needcompute) {
                v->status(CtNoCompute);
            }
        }
        void computeQueue(Output &out) {
            Node *root = out.node();
            std::size_t nums = 0;
            std::deque<std::pair<Node *, std::size_t>> tmp;

            if (root == NULL) {
                return;
            }

            tmp.push_back(std::make_pair(root, 0));
            while (!tmp.empty()) {
                root = tmp.back().first;
                if (root == NULL)
                    continue;
                nums = root->num_inputs();
                if (!tmp.back().second) {
                    tmp.back().second = 1;
                    for (size_t i = 0; i < nums; i++) {
                        tmp.push_back(std::make_pair(root->input(nums - i - 1), 0));
                    }
                }
                else {
                    switch (root->type()) {
                    case NtVariable:
                    case NtPlaceholder:
                        if (root->status() != CtComputed) {
                            std::cout << "[Error] Variabley '" << root->name() << "' is not init!!!" << std::endl;
                            needcompute.clear();
                            return;
                        }
                        break;
                    case NtOperation:
                    case NtGradOp:
                        if ((root->status() == CtNoCompute)) {
                            root->status(CtQueuing);
                            needcompute.push_back(root);
                        }
                        break;
                    default:
                        break;
                    }
                    tmp.pop_back();
                }
            }
        }

    public:
        GraphImpl &opName(std::string name) {
            op_named = name;
            return *this;
        }
        void computeQueue2(Output &out) {
            Node* root = out.node();
            needcompute.clear();
            if (root->type() == NtInitOp) {
                needcompute.push_back(root);
            }
            else {
                computeQueue(out);
            }
        }
        void run(Output out) {
            computeQueue2(out);
            compute();
            return;
        }
        void run(Output out, const std::initializer_list<std::pair<std::string, Input::Initializer>> &v) {
            std::map<std::string, Node *>::iterator it;
            for (auto n : v) {
                it = named.find(n.first);
                if ((it != named.end()) && (it->second->type() == NtPlaceholder)) {
                    ((NodePlaceholder*)(it->second))->assign(n.second.tensor);
                }
            }
            computeQueue2(out);
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
    Graph::Graph():impl(new GraphImpl()) {}
    Graph& Graph::opName(std::string name) {
        impl->opName(name);
        return *this;
    }
    void Graph::run(Output out) {
        impl->run(out);
    }
    void Graph::run(Output out, const std::initializer_list<std::pair<std::string, Input::Initializer>> &v) {
        impl->run(out,v);
    }
    Output Graph::insert(const std::shared_ptr<Node> nptr) {
        return impl->insert(nptr);
    }
    Output Graph::initAllVariable() {
        return impl->initAllVariable();
    }
} // namespace cactus