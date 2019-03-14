
#ifndef CACTUS_EIGEN3_COND_HPP
#define CACTUS_EIGEN3_COND_HPP
#include "common.hpp"
#include "four_operations.hpp"
//#include "pow.hpp"
//#include "func.hpp"
//#include "cc.hpp"

namespace cactus {
    /*REG_OP(int, NoneGradOp, > );
    REG_OP(int, NoneGradOp, < );
    REG_OP(int, NoneGradOp, >=);
    REG_OP(int, NoneGradOp, <=);
    REG_OP(int, NoneGradOp, != );
    REG_OP(int, NoneGradOp, == );*/
    REG_OP(REG_RET_TYPE, AddGradOp, +);
    REG_OP(REG_RET_TYPE, SubGradOp, -);
    REG_OP(REG_RET_TYPE, MulGradOp, *);
    REG_OP(REG_RET_TYPE, DivGradOp, /);
    /*REG_FUNC_OP(LogGradOp, log);
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
}
#endif