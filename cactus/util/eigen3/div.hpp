
#ifndef CACTUS_EIGEN3_MULOP_HPP
#define CACTUS_EIGEN3_MULOP_HPP
#include "common.hpp"

namespace cactus {
    template<typename RET, typename LV, typename RV>
    class MulGradOp :public GradOp {
    public:
        MulGradOp() :name_("MulGradOp") {}
        MulGradOp(tensor<RET>& res, tensor<LV>& lv, tensor<RV>& rv)
            :name_("MulGradOp"), res_(res), lv_(lv), rv_(rv)
        {

        }
        ~MulGradOp() {

        }
        virtual int backward() {
            lv_.setGrad(res_.grad()*rv_);
            rv_.setGrad(res_.grad()*lv_);
            return 0;
        }
        virtual std::vector<GradOp*> oplist() {
            return{ lv_.gop(),rv_.gop() };
        }
    private:
        std::string name_;
        tensor<RET> res_;
        tensor<LV> lv_;
        tensor<RV> rv_;
    };
    template<typename LV, typename RV>
    tensor<typename std::result_of<S<LV, RV>()>::type> operator *(tensor<LV>& lv, tensor<RV>& rv) {
        using result_type = typename std::result_of<S<LV, RV>()>::type;
        tensor<result_type> val;
        val.bindOp(std::make_shared<MulGradOp<result_type, LV, RV>>(val, lv, rv));
        //arithmetic_eigen(val, lv, rv, *);
        if (lv.size() == rv.size()) {
            val.reshape(lv.shape());
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = x.cast<result_type>() * y.cast<result_type>();
        }
        else if (lv.size() == 1) {
            val.reshape(rv.shape());
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = (result_type)lv.ref({ 0 }) * y.cast<result_type>();
        }
        else if (rv.size() == 1) {
            val.reshape(lv.shape());
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size());
            z = x.cast<result_type>() * (result_type)rv.ref({ 0 });
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