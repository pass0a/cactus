
#ifndef CACTUS_EIGEN3_COND_HPP
#define CACTUS_EIGEN3_COND_HPP
#include "common.hpp"
//#include "four_operations.hpp"
//#include "pow.hpp"
//#include "func.hpp"

namespace cactus {
    /*REG_OP(int, NoneGradOp, > );
    REG_OP(int, NoneGradOp, < );
    REG_OP(int, NoneGradOp, >=);
    REG_OP(int, NoneGradOp, <=);
    REG_OP(int, NoneGradOp, != );
    REG_OP(int, NoneGradOp, == );
    REG_OP(REG_RET_TYPE, AddGradOp, +);
    REG_OP(REG_RET_TYPE, SubGradOp, -);
    REG_OP(REG_RET_TYPE, MulGradOp, *);
    REG_OP(REG_RET_TYPE, DivGradOp, /);
    REG_FUNC_OP(LogGradOp, log);
    REG_FUNC_OP(AbsGradOp, abs);
    REG_FUNC_OP(SqrtGradOp, sqrt);
    REG_FUNC_OP(NoneGradOp, log10);
    REG_FUNC_OP(NoneGradOp, exp);
    REG_FUNC_OP(NoneGradOp, sin);
    REG_FUNC_OP(NoneGradOp, cos);
    REG_FUNC_OP(NoneGradOp, tan);
    REG_FUNC_OP(NoneGradOp, asin);
    REG_FUNC_OP(NoneGradOp, acos);
    REG_FUNC_OP(NoneGradOp, atan);
    REG_FUNC_OP(NoneGradOp, sinh);
    REG_FUNC_OP(NoneGradOp, cosh);
    REG_FUNC_OP(NoneGradOp, tanh);
    REG_FUNC_OP(NoneGradOp, arg);
    REG_FUNC_OP(NoneGradOp, floor);
    REG_FUNC_OP(NoneGradOp, ceil);
    REG_FUNC_OP(NoneGradOp, round);
    REG_FUNC_OP(NoneGradOp, isfinite);
    REG_FUNC_OP(NoneGradOp, isinf);
    REG_FUNC_OP(NoneGradOp, isnan);*/
    template<typename LV, typename RV>
    tensor<typename std::result_of<S<LV, RV>()>::type> operator * (tensor<LV>& lv, tensor<RV>& rv) {

        using result_type = typename std::result_of<S<LV, RV>()>::type;
        using namespace Eigen;
        tensor<result_type> val;
        val.bindOp(std::make_shared<NoneGradOp<result_type, LV, RV>>(val, lv, rv));
        if (lv.size() == rv.size()) {

            val.reshape(lv.shape());
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            auto tmp = x.cast<result_type>() * y.cast<result_type>();
            z = tmp.cast<result_type>();
        }
        else if (lv.size() == 1) {

            val.reshape(rv.shape());
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            auto tmp = (result_type)lv.ref({ 0 }) * y.cast<result_type>();
            z = tmp.cast<result_type>();
        }
        else if (rv.size() == 1) {

            val.reshape(lv.shape());
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size());
            auto tmp = x.cast<result_type>() *(result_type)rv.ref({ 0 });
            z = tmp.cast<result_type>();
        }
        return val;
    }
    template<typename LV, typename RV>
    tensor<typename std::result_of<S<LV, RV>()>::type> operator *(tensor<LV>& lv, RV rv) {
        tensor<RV> val = rv; 
        return lv * val; 
    }
}
#endif