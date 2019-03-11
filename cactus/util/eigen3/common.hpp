#ifndef CACTUS_EIGEN3_COMMON_HPP
#define CACTUS_EIGEN3_COMMON_HPP
#include "../../../3rd/eigen/Eigen/Dense"
#include "../../core/framework/tensor.hpp"
namespace cactus {
    

    template<typename Tx, typename Ty>
    struct S {
        auto operator()() { return Tx(0) + Ty(0); }
    };

#define REG_RET_TYPE typename std::result_of<S<LV, RV>()>::type
#define REG_OP(ret_type,grad_op,op_type) \
    template<typename LV, typename RV>\
    tensor<ret_type> operator op_type (tensor<LV>& lv, tensor<RV>& rv) {\
        using result_type = typename std::result_of<S<LV, RV>()>::type;\
        using namespace Eigen;\
        tensor<ret_type> val;\
        val.bindOp(std::make_shared<grad_op<ret_type, LV, RV>>(val, lv, rv)); \
        if (lv.size() == rv.size()) {\
            val.reshape(lv.shape());\
            Map<Array<ret_type, Dynamic, RowMajor>>\
                z(val.data(), val.size());\
            Map<Array<LV, Dynamic, RowMajor>>\
                x(lv.data(), lv.size());\
            Map<Array<RV, Dynamic, RowMajor>>\
                y(rv.data(), rv.size());\
            auto tmp = x.cast<result_type>() op_type y.cast<result_type>();\
            z = tmp.cast<ret_type>();\
        }\
        else if (lv.size() == 1) {\
            val.reshape(rv.shape());\
            Map<Array<ret_type, Dynamic, RowMajor>>\
                z(val.data(), val.size());\
            Map<Array<RV, Dynamic, RowMajor>>\
                y(rv.data(), rv.size());\
            auto tmp = (result_type)lv.ref({ 0 }) op_type y.cast<result_type>();\
            z = tmp.cast<ret_type>();\
        }\
        else if (rv.size() == 1) {\
            val.reshape(lv.shape());\
            Map<Array<ret_type, Dynamic, RowMajor>>\
                z(val.data(), val.size());\
            Map<Array<LV, Dynamic, RowMajor>>\
                x(lv.data(), lv.size());\
            auto tmp = x.cast<result_type>() op_type (result_type)rv.ref({ 0 });\
            z = tmp.cast<ret_type>();\
        }\
        return val;\
    }\
    template<typename LV, typename RV>\
    tensor<ret_type> operator op_type(tensor<LV>& lv, RV rv) {\
        tensor<RV> val = rv;\
        return lv op_type val;\
    }
#define REG_FUNC_OP(grad_op,op_func) \
    template<typename LV>\
    tensor<LV> op_func(tensor<LV>& lv) {\
        using namespace Eigen;\
        tensor<LV> val;\
        val.bindOp(std::make_shared<grad_op<LV>>(val, lv)); \
        val.reshape(lv.shape());\
        Map<Array<LV, Dynamic, RowMajor>>\
            z(val.data(), val.size());\
        Map<Array<LV, Dynamic, RowMajor>>\
            x(lv.data(), lv.size());\
        z = op_func(x);\
        return val;\
    }
}

#endif