/*
    Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_OPS_HPP_
#define SRC_OPS_HPP_

#include "tensor.hpp"

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
/*class Input {
public:
        
};
class InputList {
public:
    InputList(const std::initializer_list<Input>& v) :l(v.begin(), v.end()) {
    }
private:
    std::vector<Input> l;
};*/
const Tensor& Const(const Initalizer& v) {
    return v.tensor;
}
}  // namespace cactus

#endif  // SRC_OPS_HPP_
