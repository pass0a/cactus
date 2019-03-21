
#ifndef CACTUS_EIGEN3_FUNC_HPP
#define CACTUS_EIGEN3_FUNC_HPP

namespace cactus {
    template<typename LV>
    class LogGradOp :public GradOp {
    public:
        LogGradOp() :name_("LogGradOp") {}
        LogGradOp(tensor<LV>& res, tensor<LV>& lv)
            :name_("LogGradOp"), res_(res), lv_(lv)
        {

        }
        ~LogGradOp() {

        }
        virtual int backward() {
            //lv_.setGrad(res_.grad() / rv_);
            //rv_.setGrad(res_.grad()*lv_);
            return 0;
        }
        virtual void reback() { lv_.reback(); }
        virtual std::vector<GradOp*> oplist() {
            return{ lv_.gop() };
        }
    private:
        std::string name_;
        tensor<LV> res_;
        tensor<LV> lv_;
    };
    template<typename LV>
    class AbsGradOp :public GradOp {
    public:
        AbsGradOp() :name_("AbsGradOp") {}
        AbsGradOp(tensor<LV>& res, tensor<LV>& lv)
            :name_("AbsGradOp"), res_(res), lv_(lv)
        {

        }
        ~AbsGradOp() {

        }
        virtual int backward() {
            /*tensor<LV> x = res;
            tensor<LV> tmp=sqrt(pow(res_, 2));
            tmp.backward();
            lv_.setGrad(x.grad());*/
            return 0;
        }
        virtual void reback() { lv_.reback(); }
        virtual std::vector<GradOp*> oplist() {
            return{ lv_.gop() };
        }
    private:
        std::string name_;
        tensor<LV> res_;
        tensor<LV> lv_;
    };
    template<typename LV>
    class SqrtGradOp :public GradOp {
    public:
        SqrtGradOp() :name_("SqrtGradOp") {}
        SqrtGradOp(tensor<LV>& res, tensor<LV>& lv)
            :name_("SqrtGradOp"), res_(res), lv_(lv)
        {

        }
        ~SqrtGradOp() {

        }
        virtual int backward() {
            lv_.setGrad(res_.grad()*pow(lv_, -0.5)*0.5);
            return 0;
        }
        virtual void reback() { lv_.reback();  }
        virtual std::vector<GradOp*> oplist() {
            return{ lv_.gop() };
        }
    private:
        std::string name_;
        tensor<LV> res_;
        tensor<LV> lv_;
    };
}
#endif