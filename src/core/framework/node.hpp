
#ifndef SRC_NODE_HPP_
#define SRC_NODE_HPP_

#include "tensor.hpp"
#include <cstring>
#include <iostream>
#include <vector>
//#include <vector>

namespace cactus {
    class Operation;
    class Node;
    typedef std::vector<std::pair<Node*, Tensor>> xgrads;
    enum NodeType { NtPlaceholder, NtVariable, NtConst, NtInitOp, NtGradOp, NtOperation };
    enum ComputeStatus { CtNoCompute, CtComputed, CtQueuing };
    class Node {
    public:
        Node() : cstatus_(CtNoCompute) {}
        virtual std::size_t num_inputs() { return 0; }
        virtual Node *input(std::size_t) { return NULL; }
        ComputeStatus status() { return cstatus_; };
        void status(ComputeStatus cs) { cstatus_ = cs; };
        virtual NodeType type() = 0;
        void run() {
            compute();
            status(CtComputed);
        }
        virtual void compute() { std::cout << "Node:" << type() << std::endl; }
        virtual xgrads grad(Tensor&) {
            return xgrads();
        }
        Tensor &tensor() { return t; }
        std::string name() { return name_; }
        void name(std::string v) { name_ = v; }

    protected:
        Tensor t;
        std::string name_;
        ComputeStatus cstatus_;
    };

    class NodePlaceholder : public Node {
    public:
        NodePlaceholder(Shape s, DataType dt) {}
        NodeType type() { return NtPlaceholder; }
        void assign(const Tensor& v) {
            t = v;
            status(CtComputed);
        }
    };
    class NodeVariable : public Node {
    public:
        NodeVariable(const Tensor &v) { init_val = v; }
        NodeType type() { return NtVariable; }
        virtual void compute() {
            t = init_val;
            status(CtComputed);
        }
    private:
        Tensor init_val;
    };
    class NodeConst : public Node {
    public:
        NodeConst(const Tensor &v) { cstatus_ = (CtNoCompute); t = v; }
        NodeType type() { return NtConst; }
    };

    class Output {
    public:
        Output() : node_(NULL) {}
        Output(const Output &o) { node_ = o.node(); }
        Output(Node *n) : node_(n) {}
        Node *node() const {
            assert(node_ != NULL);
            return node_;
        }
        Tensor& tensor() {
            assert(node_ != NULL);
            return node_->tensor();
        }
    private:
        Node *node_;
    };

    class Input {
    public:
        struct Initializer {
            template <typename T> Initializer(const T &v) {
                Shape s = { 1, 1 };
                tensor = Tensor(DataTypeToEnum<T>::value, s);
                std::memcpy(tensor.data(), &v, tensor.totalBytes());
            }
            template <typename T> Initializer(const std::initializer_list<T> &v) {
                Shape s = { 1,v.size() };
                tensor = Tensor(DataTypeToEnum<T>::value, s);
                std::memcpy(tensor.data(), v.begin(), tensor.totalBytes());
            }
            Initializer(const Output& v) {
                tensor.assign(v.node()->tensor());
            }
            Initializer(const std::initializer_list<Initializer> &v) {
                uint32_t offset = 0;
                auto const &first = *v.begin();
                Shape s = { v.size(),first.tensor.shape().cols  };
                tensor = Tensor(first.tensor.dtype(), s);

                for (auto n : v) {
                    std::memcpy((char *)tensor.data() + offset, n.tensor.data(),
                        n.tensor.totalBytes());
                    offset += n.tensor.totalBytes();
                }
            }
            Tensor tensor;
        };

    public:
        Input(Output out) : output_(out) {}
        Node *node() const { return output_.node(); }
        // Input(const Initializer& init){}
        /*template<typename T>
        Input(const T& v): Input(Initializer(v)) {}*/
        /*const Tensor& tensor() const {
            return tensor_;
        }*/
    private:
        Input() {}
        Output output_;
        // Tensor tensor_;
    };

    class Operation : public Node {
    public:
        void input(Node *v) { inputs.push_back(v); }
        Node *input(std::size_t idx) {
            if (idx < inputs.size()) {
                return inputs.at(idx);
            }
            return NULL;
        }
        std::size_t num_inputs() { return inputs.size(); }
        /*Output output(uint32_t idx) {
            return Output(this);
        }*/

        NodeType type() { return NtOperation; }

    protected:
        std::vector<Node *> inputs;
    };
} // namespace cactus

#endif // SRC_NODE_HPP_
