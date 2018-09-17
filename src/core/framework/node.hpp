
#ifndef SRC_NODE_HPP_
#define SRC_NODE_HPP_

#include "tensor.hpp"
#include <cstring>
#include <iostream>

namespace cactus {

class Operation;
enum NodeType {
    NtPlaceholder,
    NtVariables,
    NtConst,
    NtScalar,
    NtOperation
};
class Node {
public:
    Node() {}
    /*std::size_t num_inputs() {
        return inputs.size();
    }
    std::size_t num_outputs() {
        return outputs.size();
    }*/
    virtual NodeType type() = 0;
private:
    /*std::vector<std::shared_ptr<Node>> inputs;
    std::vector<std::shared_ptr<Node>> outputs;*/
};

class NodePlaceholder:public Node {
public:
    NodeType type() {
        return NtPlaceholder;
    }
private:

};
class NodeVariables :public Node {
public:
    NodeType type() {
        return NtVariables;
    }
private:
    Tensor t;
};
class NodeConst :public Node {
public:
    NodeConst(const Tensor& v):t(v) {}
    NodeType type() {
        return NtConst;
    }
    const Tensor& tensor() {
        return t;
    }
private:
    Tensor t;
};

class Output {
public:
    Output() :node_(NULL) {}
    Output(const Output& o) { node_=o.node(); }
    Output(Node* n) :node_(n) {}
    Node* node() const { return node_; }
private:
    Node* node_;
};

class Input{
public:
    struct Initializer {
        template<typename T>
        Initializer(const T& v) {
            Shape s = { 1, 1 };
            tensor = Tensor(DataTypeToEnum<T>::value, s);
            std::memcpy(tensor.data(),
                &v,
                tensor.TotalBytes());
        }
        template<typename T>
        Initializer(const std::initializer_list<T>& v) {
            Shape s = { 1, v.size() };
            tensor = Tensor(DataTypeToEnum<T>::value, s);
            std::memcpy(tensor.data(),
                v.begin(),
                tensor.TotalBytes());
        }
        Initializer(const std::initializer_list<Initializer>& v) {
            uint32_t offset = 0;
            auto const & first = *v.begin();
            Shape s={ first.tensor.shape().cols , v.size() };
            tensor = Tensor(first.tensor.dtype(),s);

            for (auto n:v){
                std::memcpy(tensor.data(),n.tensor.data(),n.tensor.TotalBytes());
            }
        }
        Tensor tensor;
    };
    
public:
    Input(Output& out):output_(out){}
    Node* node() const { return output_.node(); }
    //Input(const Initializer& init){}
    /*template<typename T>
    Input(const T& v): Input(Initializer(v)) {}*/
    /*const Tensor& tensor() const {
        return tensor_;
    }*/
private:
    Input() {}
    Output output_;
    //Tensor tensor_;
};

class Operation :public Node{
public:
    void put(Input v) {
        inputs.push_back(v);
    }
    Output get(uint32_t idx) {
        return outputs[idx];
    }
    NodeType type() {
        return NtOperation;
    }
    virtual void compute() = 0;
protected:
    std::vector<Input> inputs;
    std::vector<Output> outputs;
};
}

#endif  // SRC_NODE_HPP_
