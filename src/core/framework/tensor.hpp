/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_TENSOR_HPP_
#define SRC_TENSOR_HPP_

#include "buffer.hpp"
#include "types.h"


namespace cactus{
struct Shape {
    uint32_t rows;
    uint32_t cols;
    int operator==(const Shape& v) const {
        if ((rows == v.rows) && (cols == v.cols)) {
            return 1;
        }
        return 0;
    }
};

class Tensor {
public:
    Tensor();
    Tensor(DataType type, Shape s);
    template<typename T>
    Tensor(T scalar) {
        init(DataTypeToEnum<T>::value, {1,1});
        *(T*)data() = scalar;
    }
    uint32_t TotalBytes();
    void* data();
    DataType dtype() const;
    const Shape& shape() const;
    template<typename T>
    T get(int pos) {
        return ((T*)data())[pos];
    }
private:
    void init(const DataType& type,const Shape& s);
private:
    Buffer buf_;
    DataType dtype_;
    Shape shape_;
};
}

#endif  // SRC_TENSOR_HPP_

