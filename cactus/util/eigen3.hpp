#ifndef CACTUS_EIGEN3_HPP
#define CACTUS_EIGEN3_HPP

#include "../3rd/eigen/Eigen/Dense"
#include "../core/framework/tensor.h"

namespace cactus {

    using namespace Eigen;
    template<typename LV, typename RV>
    tensor<LV> operator +(tensor<LV> lv, tensor<RV> rv) {
        /*Map<Matrix<Type::value_type, Dynamic, Dynamic, RowMajor>>
        x;*/
        return lv;
    }
    template<typename LV, typename RV>
    tensor<LV> operator +(tensor<LV>& lv, RV rv) {
        auto sh=lv.shape();
        Map<Array<LV, Dynamic, Dynamic, RowMajor>>
        x(lv.data(),sh[0],sh[1]);
        x+=rv;
        return lv;
    }
}
#endif