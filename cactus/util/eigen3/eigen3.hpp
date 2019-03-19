#ifndef CACTUS_EIGEN3_HPP
#define CACTUS_EIGEN3_HPP

#include "operator.hpp"

namespace cactus {
    using namespace Eigen;
    template<typename T>
    class T2V {
    public:
        T2V(T* data, size_t x, size_t y) {}
        auto array(T* data,size_t x, size_t y) {
            Map<Array<T, Dynamic, Dynamic, RowMajor>> tmp(data,x,y);
            return tmp;
        }
    };
    template<typename Type>
    std::ostream & operator<<(std::ostream & os, tensor<Type>& stu)
    {
        // TODO: 在此处插入 return 语句
        os << stu.array();
        return os;
    }
    
    template<typename Tx,typename Ty>
    tensor<Ty> tensor_cast(tensor<Tx> in) {
        using namespace Eigen;
        tensor<Ty> val;
        /*if (std::is_same<Tx, Ty>()) {
        }
        else {
        }*/
        val.reshape(in.shape());
        Map<Array<Tx, Dynamic, RowMajor>>
            x(in.data(), in.size());
        Map<Array<Ty, Dynamic, RowMajor>>
            y(val.data(), val.size());
        y = x.cast<Ty>();
        
        return val;
    }

}
#endif