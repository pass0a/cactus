#include "node.hpp"

namespace cactus {
    Node::Node() : cstatus_(CtNoCompute) {}
    std::size_t Node::num_inputs() { return 0; }
    Node *Node::input(std::size_t) { return NULL; }
    ComputeStatus Node::status() { return cstatus_; };
    void Node::status(ComputeStatus cs) { cstatus_ = cs; };
    void Node::run() {
        compute();
        status(CtComputed);
    }
    void Node::compute() { std::cout << "Node:" << type() << std::endl; }
    xgrads Node::grad(Tensor&) {
        return xgrads();
    }
    Tensor& Node::tensor() { return t; }
    std::string Node::name() { return name_; }
    void Node::name(std::string v) { name_ = v; }

    NodePlaceholder::NodePlaceholder(Shape s, DataType dt) {}
    NodeType NodePlaceholder::type() { return NtPlaceholder; }
    void NodePlaceholder::assign(const Tensor& v) {
        t = v;
        status(CtComputed);
    }
    NodeVariable::NodeVariable(const Tensor &v) { init_val = v; }
    NodeType NodeVariable::type() { return NtVariable; }
    void NodeVariable::compute() {
        t = init_val;
        status(CtComputed);
    }
    NodeConst::NodeConst(const Tensor &v) { cstatus_ = (CtNoCompute); t = v; }
    NodeType NodeConst::type() { return NtConst; }

    Output::Output() : node_(NULL) {}
    Output::Output(const Output &o) { node_ = o.node(); }
    Output::Output(Node *n) : node_(n) {}
    Node *Output::node() const {
        assert(node_ != NULL);
        return node_;
    }
    Tensor& Output::tensor() {
        assert(node_ != NULL);
        return node_->tensor();
    }
    
    template<typename T>
    void dumplog(Tensor& c) {
        auto s = c.shape();
        for (size_t i = 0; i < s.rows; i++)
        {
            for (size_t j = 0; j < s.cols; j++)
            {
                std::cout << c.get<T>(i*s.rows + j);
            }
        }
        std::cout << std::endl;
    }
    void Output::dump()
    {
        Tensor x = tensor();
        CASES(x.dtype(), dumplog<T>(x));
    }

    Input::Initializer::Initializer(const Output& v) {
        tensor.assign(v.node()->tensor());
    }
    Input::Initializer::Initializer(const std::initializer_list<Initializer> &v) {
        uint32_t offset = 0;
        auto const &first = *v.begin();
        Shape s = { v.size(),first.tensor.shape().cols };
        tensor = Tensor(first.tensor.dtype(), s);

        for (auto n : v) {
            std::memcpy((char *)tensor.data() + offset, n.tensor.data(),
                n.tensor.totalBytes());
            offset += n.tensor.totalBytes();
        }
    }

    Input::Input(Output out) : output_(out) {}
    Node* Input::node() const { return output_.node(); }
    Input::Input() {}
    void Operation::input(Node *v) { inputs.push_back(v); }
    Node* Operation::input(std::size_t idx) {
        if (idx < inputs.size()) {
            return inputs.at(idx);
        }
        return NULL;
    }
    std::size_t Operation::num_inputs() { return inputs.size(); }
    NodeType Operation::type() { return NtOperation; }
} // namespace cactus