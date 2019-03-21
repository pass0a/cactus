#ifndef CACTUS_EIGEN3_COMMON_HPP
#define CACTUS_EIGEN3_COMMON_HPP
#include "../../../3rd/eigen/Eigen/Dense"
#include "../../core/framework/tensor.hpp"
#include <vector>
namespace cactus {
    struct xrange {
        int start;
        int len;
    };
    template<typename T>
    class comput {
    public:
        using shape_type = typename std::vector<size_t>;
        using xranges = typename std::vector<xrange>;
        using mat_type = Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>;
        static decltype(auto) matrix(T* data,shape_type sh) {
            using namespace Eigen;
            mat_type tmp(data,sh[0],sh[1]);
            return tmp.block(0, 0, sh[0], sh[1]);
        }
        static decltype(auto) matrix(T* data, shape_type sh,xranges xrgs){
            using namespace Eigen;
            mat_type tmp(data, sh[0], sh[1]);
            return tmp.block(xrgs[0].start,xrgs[1].start, xrgs[0].len, xrgs[1].len);
        }
    };
    template<typename T>
    using Tensor = tensor<T, xt::xarray<T,comput<T>>>;
    template<typename T>
    using Xscalar = tensor<T, xt::xscalar<xt::xarray<T, comput<T>>>>;
    template<typename Tx, typename Ty>
    struct S {
        auto operator()() { return Tx(0) + Ty(0); }
    };

#define REG_RET_TYPE typename std::result_of<S<LV, RV>()>::type
#define REG_OP(ret_type,grad_op,op_type) \
    template<\
        typename LV,\
        typename LVlayout,\
        typename RV,\
        typename RVlayout>\
    decltype(auto) operator op_type (tensor<LV, LVlayout>& lv, tensor<RV, RVlayout>& rv) {\
        Tensor<ret_type> tmp;\
        auto lvsh = lv.shape(), rvsh = rv.shape();\
        if (std::equal(lvsh.begin(), lvsh.end(), rvsh.begin())) {\
            tmp.reshape(lvsh);\
            auto t=lv.value().array() op_type rv.value().array();\
            tmp.value() = t.cast<ret_type>();\
        }\
        return tmp;\
    }\
    template<\
        typename LV,\
        typename LVlayout,\
        typename RV>\
    decltype(auto) operator op_type (tensor<LV, LVlayout>& lv, RV rv) {\
        Tensor<ret_type> tmp(lv.shape());\
        Xscalar<RV> val = rv;\
        auto t=lv.value().array() op_type val.value();\
        tmp.value() = t.cast<ret_type>();\
        return tmp;\
    }\
    template<\
        typename LV,\
        typename RV,\
        typename RVlayout>\
    decltype(auto) operator op_type (LV lv, tensor<RV, RVlayout>& rv) {\
        Tensor<ret_type> tmp(rv.shape());\
        Xscalar<LV> val = lv;\
        auto t=val.value() op_type rv.value().array();\
        tmp.value() = t.cast<ret_type>();\
        return tmp;\
    }
#define REG_FUNC_OP(grad_op,op_func) \
    template<typename LV,typename LVlayout>\
    Tensor<LV> op_func(tensor<LV,LVlayout>& lv) {\
        using namespace Eigen;\
        Tensor<LV> tmp;\
        tmp.reshape(lv.shape());\
        tmp.value() = op_func(lv.value().array());\
        return tmp;\
    }
}

#endif