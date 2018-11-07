
#ifndef SRC_NODE_HPP_
#define SRC_NODE_HPP_

#include "tensor.hpp"
#include <string>
#include <iostream>
#include <vector>
//#include <vector>

namespace cactus {
    class Operation;
    class Node;
    class Graph;
    class Input;
    class Output;
    struct Initializer;

    typedef std::vector<std::pair<Node*, Tensor>> xgrads;
    enum NodeType { NtPlaceholder, NtVariable, NtConst, NtInitOp, NtGradOp, NtOperation };
    enum ComputeStatus { CtNoCompute, CtComputed, CtQueuing };
    class Node {
    public:
        Node();
        virtual std::size_t num_inputs();
        virtual Node *input(std::size_t);
        ComputeStatus status();
        void status(ComputeStatus cs);
        virtual NodeType type() = 0;
        void run();
        virtual void compute();
        virtual xgrads grad(Tensor&);
        Tensor &tensor();
        std::string name();
        void name(std::string v);
    protected:
        Tensor t;
        std::string name_;
        ComputeStatus cstatus_;
    };

    class NodePlaceholder : public Node {
    public:
        NodePlaceholder(Shape s, DataType dt);
        NodeType type();
        void assign(const Tensor& v);
    };
    class NodeVariable : public Node {
    public:
        NodeVariable(const Tensor &v);
        NodeType type();
        virtual void compute();
    private:
        Tensor init_val;
    };
    class NodeConst : public Node {
    public:
        NodeConst(const Tensor &v);
        NodeType type();
    };
    
    
    Cx_EXPORTS std::ostream& operator<<(std::ostream &os, Output& stu);
    class Cx_EXPORTS Output {
    public:
        Output operator+(Initializer rhs);
    public:
        Output();
        Output(const Output &o);
        Output(Node *n);
        Output(Graph* g,Node *n);
        Node *node() const;
        Tensor& tensor();
        friend std::ostream& operator<<(std::ostream &os, Output& stu);
    private:
        Node *node_;
        Graph* g_;
    };
    struct Cx_EXPORTS Initializer {
        template <typename T> Initializer(const T &v) {
            Shape s = { 1, 1 };
            tensor = Tensor(DataTypeToEnum<T>::value, s);
            std::memcpy(tensor.data(), &v, tensor.totalBytes());
            err = 1;
        }
        template <typename T> Initializer(const std::initializer_list<T> &v) {
            Shape s = { 1,v.size() };
            tensor = Tensor(DataTypeToEnum<T>::value, s);
            std::memcpy(tensor.data(), v.begin(), tensor.totalBytes());
        }
        Initializer(const Output& v);
        Initializer(const std::initializer_list<Initializer> &v);
        Tensor tensor;
        int err=0;
    };
    class Cx_EXPORTS Input {
    public:
        Input(Output out);
        Node *node() const;
        // Input(const Initializer& init){}
        /*template<typename T>
        Input(const T& v): Input(Initializer(v)) {}*/
        /*const Tensor& tensor() const {
            return tensor_;
        }*/
    private:
        Input();
        Output output_;
        // Tensor tensor_;
    };

    class Operation : public Node {
    public:
        void input(Node *v);
        Node *input(std::size_t idx);
        std::size_t num_inputs();
        /*Output output(uint32_t idx) {
            return Output(this);
        }*/
        template<typename LT,typename RT>
        void compute() {}
        NodeType type();

    protected:
        std::vector<Node *> inputs;
    };
} // namespace cactus

#endif // SRC_NODE_HPP_
