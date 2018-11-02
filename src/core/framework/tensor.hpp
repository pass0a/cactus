/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_TENSOR_HPP_
#define SRC_TENSOR_HPP_

#include "buffer.hpp"
#include "types.h"
#include <cstring>

namespace cactus{

struct Cx_EXPORTS Shape {
    std::size_t rows;
    std::size_t cols;
    Shape();
    Shape(std::size_t r, std::size_t c);
    int operator==(const Shape& v) const;
    int operator!=(const Shape& v) const;
    int total() const;
};

class Cx_EXPORTS Tensor {
public:
    Tensor();
    Tensor(DataType type, Shape s);
    template<typename T>
    Tensor(T scalar) :dtype_(kInvalid) {
      DataType dt=DataTypeToEnum<T>::value;
      init(dt, {1,1});
        *(T*)data() = scalar;
    }
    uint32_t totalBytes() const;
    void* data() const;
    DataType dtype() const;
    const Shape& shape() const;
    template<typename T>
    T get(uint32_t pos) const {
      if(buf_.size()>pos){
        return ((T*)data())[pos];
      }
      return T(0);
    }
    template<typename T>
    void set(int pos,T val) const {
        ((T*)data())[pos]=val;
    }
    template<typename T>
    void full(T val) {
        
    }
    void assign(void * src, std::size_t len);
    void assign(const Tensor & t);
private:
    void init(const DataType& type, const Shape& s);
private:
    Buffer buf_;
    DataType dtype_;
    Shape shape_;
};

}

#endif  // SRC_TENSOR_HPP_

