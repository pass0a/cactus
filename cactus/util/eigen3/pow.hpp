
#ifndef CACTUS_EIGEN3_POW_HPP
#define CACTUS_EIGEN3_POW_HPP
#include "common.hpp"

namespace cactus {
    template<
        typename LV,
        typename LVlayout,
        typename RV,
        typename RVlayout>
        decltype(auto) pow (tensor<LV, LVlayout>& lv, tensor<RV, RVlayout>& rv) {
        using namespace Eigen;
        using ret_type = REG_RET_TYPE;
        Tensor<ret_type> tmp;
        auto lvsh = lv.shape(), rvsh = rv.shape();
        if (std::equal(lvsh.begin(), lvsh.end(), rvsh.begin())) {
            tmp.reshape(lvsh);
            tmp.value() = pow(lv.value().cast<ret_type>().array(),rv.value().cast<ret_type>().array());
        }
        return tmp;
    }
    template<
        typename LV,
        typename LVlayout,
        typename RV>
        decltype(auto) pow (tensor<LV, LVlayout>& lv, const RV& rv) {
        using namespace Eigen;
        using ret_type = REG_RET_TYPE;
        Tensor<REG_RET_TYPE> tmp(lv.shape());
        Xscalar<RV> val(rv);
        auto t = pow(lv.value().array(),val.value());
        tmp.value() = t.cast<ret_type>();
        return tmp;
    }
    template<
        typename LV,
        typename RV,
        typename RVlayout>
        decltype(auto) pow (const LV& lv, tensor<RV, RVlayout>& rv) {
        using namespace Eigen;
        using ret_type = REG_RET_TYPE;
        Tensor<REG_RET_TYPE> tmp(rv.shape());
        Xscalar<LV> val(lv);
        auto t = pow(val.value(), rv.value().array());
        tmp.value() = t.cast<ret_type>();
        return tmp;
    }
}
#endif