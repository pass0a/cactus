/*
    Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_OPS_HPP_
#define SRC_OPS_HPP_

#include "../framework/tensor.hpp"
#include "../framework/graph.hpp"
#include "../framework/operation.hpp"

namespace cactus {
struct Initalizer {
    template<typename T>
    Initalizer(const std::initializer_list<T>& v) {
        Shape s = { 1, v.size() };
        tensor = Tensor(DataTypeToEnum<T>::value, s);
        std::memcpy(tensor.data(),
            v.begin(),
            tensor.TotalBytes());
    }
    Initalizer(const std::initializer_list<Initalizer>& v) {
        auto const & first = *v.begin();
        Shape s = { v.size(), first.tensor.shape().cols };
        tensor = Tensor(first.tensor.dtype(), s);
        char* pos = reinterpret_cast<char*>(tensor.data());

        for (auto n : v) {
            std::memcpy(pos,
                n.tensor.data(),
                n.tensor.TotalBytes());
            pos+=n.tensor.TotalBytes();
        }
    }
    Tensor tensor;
};
//class Operation {
//public:
//    void input(std::vector<Tensor>) = 0;
//    Node* compute() = 0;
//};
//class Output {
//public:
//    Output():op(0) {}
//    Output(Node* ) {}
//private:
//    Operation op;
//};
const Tensor& Const(const Initalizer& v) {
    return v.tensor;
}
const Tensor Placeholder( DataType type, Shape s = {1,1}) {
    return Tensor(type, s);
}
}  // namespace cactus

#endif  // SRC_OPS_HPP_
