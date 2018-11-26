/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_TENSOR_HPP_
#define SRC_TENSOR_HPP_

#include "buffer.hpp"
#include "types.h"
#include <vector>

namespace cactus{

    typedef std::vector<size_t> Shape;
template<typename T>
class Tensor {
public:
    Tensor();
    Tensor(Shape s);
    Tensor(T scalar){
      
    }
    uint32_t totalBytes() const;
    T* data() const;
    const Shape& shape() const;
    void fill(T val) {
        
    }
    void assign(T * src, std::size_t len);
    void assign(const Tensor & t);
private:
    Buffer buf_;
    Shape shape_;
};

}

#endif  // SRC_TENSOR_HPP_

