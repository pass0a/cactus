#include "tensor.hpp"


namespace cactus {
uint32_t type_size(DataType type){
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
Tensor::Tensor(){
    
}
Tensor::Tensor(DataType type, Shape s) {
    uint32_t size = type_size(type);
    shape_ = s;
    dtype_ = type;
    buf_.resize(size*s.rows*s.cols);
}
uint32_t Tensor::TotalBytes()
{
    return buf_.size();
}
void * Tensor::data()
{
    return buf_.data();
}
DataType Tensor::dtype() const {
    return dtype_;
}
const Shape & Tensor::shape() const
{
    return shape_;
}
}
