
#ifndef CACTUS_EIGEN3_OPRATOR_HPP
#define CACTUS_EIGEN3_OPRATOR_HPP
#include "common.hpp"
//#include "four_operations.hpp"
#include "pow.hpp"
#include "tools.hpp"

namespace cactus {
REG_OP( int, NoneGradOp, > );
REG_OP( int, NoneGradOp, < );
REG_OP( int, NoneGradOp, >= );
REG_OP( int, NoneGradOp, <= );
REG_OP( int, NoneGradOp, != );
REG_OP( int, NoneGradOp, == );
REG_OP( REG_RET_TYPE, AddGradOp, +);
REG_OP( REG_RET_TYPE, SubGradOp, -);
REG_OP( REG_RET_TYPE, NoneGradOp, * );
REG_OP( REG_RET_TYPE, DivGradOp, / );
REG_FUNC_OP( LogGradOp, log );
REG_FUNC_OP( AbsGradOp, abs );
REG_FUNC_OP( SqrtGradOp, sqrt );
REG_FUNC_OP( NoneGradOp, log10 );
REG_FUNC_OP( NoneGradOp, exp );
REG_FUNC_OP( NoneGradOp, sin );
REG_FUNC_OP( NoneGradOp, cos );
REG_FUNC_OP( NoneGradOp, tan );
REG_FUNC_OP( NoneGradOp, asin );
REG_FUNC_OP( NoneGradOp, acos );
REG_FUNC_OP( NoneGradOp, atan );
REG_FUNC_OP( NoneGradOp, sinh );
REG_FUNC_OP( NoneGradOp, cosh );
REG_FUNC_OP( NoneGradOp, tanh );
REG_FUNC_OP( NoneGradOp, arg );
REG_FUNC_OP( NoneGradOp, floor );
REG_FUNC_OP( NoneGradOp, ceil );
REG_FUNC_OP( NoneGradOp, round );
REG_FUNC_OP( NoneGradOp, isfinite );
REG_FUNC_OP( NoneGradOp, isinf );
REG_FUNC_OP( NoneGradOp, isnan );

/*template<
    typename LV,
    typename LVlayout,
    typename RV>
    decltype(auto) operator * (tensor<LV, LVlayout>& lv, RV rv) {

    Tensor<REG_RET_TYPE> tmp(lv.shape());
    Xscalar<RV> val(rv);
    auto t = lv.value().array() * val.value();
    tmp.value() = t.cast<REG_RET_TYPE>();
    return tmp;
}
template<
    typename LV,
    typename RV,
    typename RVlayout>
    decltype(auto) operator * (LV lv, tensor<RV, RVlayout>& rv) {

    Tensor<REG_RET_TYPE> tmp(rv.shape());
    Xscalar<LV> val(lv);
    auto t = val.value() * rv.value().array();
    tmp.value() = t.cast<REG_RET_TYPE>();
    return tmp;
}*/
} // namespace cactus
#endif
