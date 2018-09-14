#include "tensor.hpp"

namespace cactus {

enum NodeType {
    NtPlaceholder,
    NtVariables,
    NtConst,
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
        Tensor tensor;
    };
    
public:
    Input() {}
    Input(const Initializer& init):tensor_(init.tensor) {}
    template<typename T>
    Input(const T& v): Input(Initializer(v)) {}
    Tensor& tensor() {
        return tensor_;
    }
private:
    Tensor tensor_;
};
class Output{
public:
    
};
class Operation :public Node{
public:
    void put(Input v) {
        inputs.push_back(v);
    }
    Output Compute() {
        //std::vector<Input>::iterator it = inputs.begin();
        for (auto it:inputs)
        {
            
        }
        return Output();
    }
    NodeType type() {
        return NtOperation;
    }
private:
    std::vector<Input> inputs;
    std::vector<Output> outputs;
};
}
