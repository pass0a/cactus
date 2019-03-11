
#ifndef CACTUS_EIGEN3_POW_HPP
#define CACTUS_EIGEN3_POW_HPP
#include "common.hpp"

namespace cactus {
    template<typename RET, typename LV, typename RV>
    class PowGradOp :public GradOp {
    public:
        PowGradOp() :name_("PowGradOp") {}
        PowGradOp(tensor<RET>& res, tensor<LV>& lv, tensor<RV>& rv)
            :name_("PowGradOp"), res_(res), lv_(lv), rv_(rv)
        {

        }
        ~PowGradOp() {

        }
        virtual int backward() {
            lv_.setGrad(res_.grad()*pow(lv_, rv_ - 1)*rv_);
            rv_.setGrad(res_.grad()*pow(lv_, rv_)*log(lv_));
            return 0;
        }
        virtual void reback() { lv_.reback(); }
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
    tensor<typename std::result_of<S<LV, RV>()>::type> pow(tensor<LV>& lv, tensor<RV>& rv) {
        using namespace Eigen;
        using result_type = typename std::result_of<S<LV, RV>()>::type;
        tensor<result_type> val;
        val.bindOp(std::make_shared<PowGradOp<result_type, LV, RV>>(val, lv, rv));
        if (lv.size() == rv.size()) {
            val.reshape({lv.size()});
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = Eigen::pow(x.cast<result_type>(), y.cast<result_type>());
        }
        if (lv.size() == 1) {
            val.reshape({ rv.size() });
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = Eigen::pow(lv.ref({0}), y.cast<result_type>());
        }
        if (rv.size() == 1) {
            val.reshape({ lv.size() });
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size());
            std::cout << x.cast<result_type>() << std::endl;
            std::cout << rv.ref({ 0 }) << std::endl;
            z = Eigen::pow(x.cast<result_type>(), rv.ref({ 0 }));
        }
        return val;
    }
    template<typename LV, typename RV>
    tensor<typename std::result_of<S<LV, RV>()>::type> pow(tensor<LV>& lv,RV rv) {
        tensor<RV> tmp(rv);
        return pow(lv, tmp);
    }
    template<typename LV, typename RV>
    tensor<typename std::result_of<S<LV, RV>()>::type> pow(LV lv, tensor<RV> rv) {
        tensor<LV> tmp(lv);
        return pow(tmp, rv);
    }
}
#endif