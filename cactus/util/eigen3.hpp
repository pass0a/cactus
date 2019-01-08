#ifndef CACTUS_EIGEN3_HPP
#define CACTUS_EIGEN3_HPP

#include "../3rd/eigen/Eigen/Dense"
#include "../core/framework/tensor.hpp"

namespace cactus {

    using namespace Eigen;
    void AddBackWardOp() {

    }
    template<typename LV,typename RV>
    tensor<LV> operator +(tensor<LV> lv, tensor<RV> rv) {
        tensor<LV> val;
        val.reshape(lv.shape());
        
        Map<Array<LV, Dynamic, RowMajor>>
            x(lv.data(),lv.size()),z(val.data(),val.size());
       
        if (rv.size() == 1) {
            z = x + rv.ref({ 0 });
        }
        else {
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = x + y.cast<LV>();
        }
        return val;
    }
    template<typename LV, typename RV>
    tensor<LV> operator +(tensor<LV> lv, RV rv) {
        tensor<RV> val=rv;
        return lv+val;
    }
    template<typename LV, typename RV>
    tensor<LV> operator *(tensor<LV> lv, tensor<RV> rv) {
        tensor<LV> val;
        val.reshape(lv.shape());

        Map<Array<LV, Dynamic, RowMajor>>
            x(lv.data(), lv.size()), z(val.data(), val.size());
        Map<Array<RV, Dynamic, RowMajor>>
            y(rv.data(), rv.size());

        z = x * y.cast<LV>();
        return val;
    }
    template<typename LV, typename RV>
    tensor<LV> operator *(tensor<LV>& lv, RV rv) {
        tensor<LV> val;
        val.reshape(lv.shape());
        Map<Array<LV, Dynamic, RowMajor>>
            x(lv.data(), val.size()), z(val.data(), val.size());
        z = x * rv;
        return val;
    }
    
    template<typename Type>
    std::ostream & operator<<(std::ostream & os, tensor<Type>& stu)
    {
        // TODO: 在此处插入 return 语句
        Map<Array<Type, Dynamic, RowMajor>>
            tmp(stu.data(),stu.size());
        os << tmp;
        return os;
    }
    template<typename Type>
    std::ostream & operator<<(std::ostream & os, xt::xarray<Type>& stu)
    {
        // TODO: 在此处插入 return 语句
        Map<Array<Type, Dynamic, RowMajor>>
            tmp(stu.data(), stu.size());
        os << tmp;
        return os;
    }
    
}
#endif