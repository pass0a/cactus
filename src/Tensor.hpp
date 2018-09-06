/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_TENSOR_HPP_
#define SRC_TENSOR_HPP_

#include "buffer.hpp"

enum class DataType {
    kFloat = 0,
    kDouble = 1,
    kHalf = 2,
    kInt8 = 3,
};

namespace cactus{
class Tensor {
public:
    Tensor(DataType type,int row=1,int col=1){
        //buf_.resize();
    }
private:
    Buffer buf_;
};
}

#endif  // SRC_TENSOR_HPP_

