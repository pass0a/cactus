
#ifndef CACTUS_EIGEN3_COND_HPP
#define CACTUS_EIGEN3_COND_HPP
#include "common.hpp"
//#include "four_operations.hpp"
//#include "pow.hpp"
//#include "func.hpp"

namespace cactus {
    REG_OP(int, NoneGradOp, > );
    REG_OP(int, NoneGradOp, < );
    REG_OP(int, NoneGradOp, >= );
    REG_OP(int, NoneGradOp, <= );
    REG_OP(int, NoneGradOp, != );
    REG_OP(int, NoneGradOp, == );
    REG_OP(REG_RET_TYPE, AddGradOp, +);
    //REG_OP(REG_RET_TYPE, SubGradOp, -);
    //REG_OP(REG_RET_TYPE, NoneGradOp, *);
    REG_OP(REG_RET_TYPE, DivGradOp, / );
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
    REG_FUNC_OP(NoneGradOp, isnan);

    template<
        typename LV,
        typename LVlayout,
        typename RV,
        typename RVlayout>
        decltype(auto) operator * (tensor<LV, LVlayout>& lv, tensor<RV, RVlayout>& rv) {

        Tensor<REG_RET_TYPE> tmp;
        auto lvsh = lv.shape(), rvsh = rv.shape();
        if (std::equal(lvsh.begin(), lvsh.end(), rvsh.begin())) {

            tmp.reshape(lvsh);
            auto t = lv.value().array() * rv.value().array();
            tmp.value() = t.cast<REG_RET_TYPE>();
        }
        return tmp;
    }
    template<
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
    }
    template<
        typename LV,
        typename LVlayout,
        typename RV,
        typename RVlayout>
        decltype(auto) operator - (tensor<LV, LVlayout>& lv, tensor<RV, RVlayout>& rv) {

        Tensor<REG_RET_TYPE> tmp;
        auto lvsh = lv.shape(), rvsh = rv.shape();
        if (std::equal(lvsh.begin(), lvsh.end(), rvsh.begin())) {

            tmp.reshape(lvsh);
            auto t = lv.value().cast<REG_RET_TYPE>().array() - rv.value().cast<REG_RET_TYPE>().array();
            tmp.value() = t.cast<REG_RET_TYPE>();
        }
        return tmp;
    }
    template<
        typename LV,
        typename LVlayout,
        typename RV>
        decltype(auto) operator - (tensor<LV, LVlayout>& lv, RV rv) {

        Tensor<REG_RET_TYPE> tmp(lv.shape());
        Xscalar<RV> val(rv);
        auto t = lv.value().array() - val.value();
        tmp.value() = t.cast<REG_RET_TYPE>();
        return tmp;
    }
    template<
        typename LV,
        typename RV,
        typename RVlayout>
        decltype(auto) operator - (LV lv, tensor<RV, RVlayout>& rv) {
		if (!std::is_same<LV, RV>()) {
			std::cout << typeid(REG_RET_TYPE).name() << typeid(RV).name() << std::endl;
		}
        Tensor<REG_RET_TYPE> tmp(rv.shape());
        Xscalar<LV> val(lv);
        auto t = val.value() - rv.value().array();
        tmp.value() = t.cast<REG_RET_TYPE>();
        return tmp;
    }
}
#endif