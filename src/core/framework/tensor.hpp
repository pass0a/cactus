/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_TENSOR_HPP_
#define SRC_TENSOR_HPP_

#include "buffer.hpp"
#include "types.h"
#include <cstring>

namespace cactus{

struct Shape {
    std::size_t rows;
    std::size_t cols;
    Shape():rows(0), cols(0) {}
    Shape(std::size_t r,std::size_t c):rows(r),cols(c) {
    }
    int operator==(const Shape& v) const {
        if ((rows == v.rows) && (cols == v.cols)) {
            return 1;
        }
        return 0;
    }
    int operator!=(const Shape& v) const {
        if ((rows != v.rows) || (cols != v.cols)) {
            return 1;
        }
        return 0;
    }
    int total() const {
        return rows*cols;
    }
};

class Tensor {
public:
    Tensor() :dtype_(kInvalid) {

    }
    Tensor(DataType type, Shape s) : dtype_(kInvalid) {
        init(type, s);
    }
    template<typename T>
    Tensor(T scalar) :dtype_(kInvalid) {
      DataType dt=DataTypeToEnum<T>::value;
      init(dt, {1,1});
        *(T*)data() = scalar;
    }
    uint32_t totalBytes() const
    {
        return buf_.size();
    }
    void* data() const
    {
        return buf_.data();
    }
    DataType dtype() const {
        return dtype_;
    }
    const Shape& shape() const
    {
        return shape_;
    }
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
    void assign(void * src, std::size_t len)
    {
        if (len > totalBytes())len = totalBytes();
        std::memcpy((char*)data(), src, len);
    }
    void assign(const Tensor & t)
    {
        //assert(t.dtype()== dtype_,t.shape() == shape_);
        init(t.dtype(), t.shape());
        std::memcpy(data(), t.data(), t.totalBytes());
    }
private:
    uint32_t type_size(DataType type) {
        switch (type) {
        case kFloat: {return sizeof(EnumToDataType<kFloat>::Type); }
        case kDouble: {return sizeof(EnumToDataType<kDouble>::Type); }
        case kInt8: {return sizeof(EnumToDataType<kInt8>::Type); }
        case kInt16: {return sizeof(EnumToDataType<kInt16>::Type); }
        case kInt32: {return sizeof(EnumToDataType<kInt32>::Type); }
        case kInt64: {return sizeof(EnumToDataType<kInt64>::Type); }
        case kUint8: {return sizeof(EnumToDataType<kUint8>::Type); }
        default: {}
        }
        return 0;
    }
    void init(const DataType& type, const Shape& s) {
        uint32_t size = type_size(type);
        shape_ = s;
        dtype_ = type;
        buf_.resize(size*s.rows*s.cols);
    }
private:
    Buffer buf_;
    DataType dtype_;
    Shape shape_;
};

}

#endif  // SRC_TENSOR_HPP_

