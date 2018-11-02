#include "tensor.hpp"

namespace cactus {
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

    Tensor::Tensor() :dtype_(kInvalid) {

    }
    Tensor::Tensor(DataType type, Shape s) : dtype_(kInvalid) {
        init(type, s);
    }
    uint32_t Tensor::totalBytes() const
    {
        return buf_.size();
    }
    void* Tensor::data() const
    {
        return buf_.data();
    }
    DataType Tensor::dtype() const {
        return dtype_;
    }
    const Shape& Tensor::shape() const
    {
        return shape_;
    }
    void Tensor::assign(void * src, std::size_t len)
    {
        if (len > totalBytes())len = totalBytes();
        std::memcpy((char*)data(), src, len);
    }
    void Tensor::assign(const Tensor & t)
    {
        //assert(t.dtype()== dtype_,t.shape() == shape_);
        init(t.dtype(), t.shape());
        std::memcpy(data(), t.data(), t.totalBytes());
    }
    void Tensor::init(const DataType& type, const Shape& s) {
        uint32_t size = type_size(type);
        shape_ = s;
        dtype_ = type;
        buf_.resize(size*s.rows*s.cols);
    }
    Shape::Shape() :rows(0), cols(0) {}
    Shape::Shape(std::size_t r, std::size_t c) :rows(r), cols(c) {
    }
    int Shape::operator==(const Shape& v) const {
        if ((rows == v.rows) && (cols == v.cols)) {
            return 1;
        }
        return 0;
    }
    int Shape::operator!=(const Shape& v) const {
        if ((rows != v.rows) || (cols != v.cols)) {
            return 1;
        }
        return 0;
    }
    int Shape::total() const {
        return rows*cols;
    }
}
