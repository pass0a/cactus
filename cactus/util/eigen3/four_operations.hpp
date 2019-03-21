
#ifndef CACTUS_EIGEN3_ADDOP_HPP
#define CACTUS_EIGEN3_ADDOP_HPP

namespace cactus {
    template<typename RET, typename LV, typename RV>
    class AddGradOp :public GradOp {
    public:
        AddGradOp() :name_("AddGradOp") {}
        AddGradOp(tensor<RET>& res, tensor<LV>& lv, tensor<RV>& rv)
            :name_("AddGradOp"), res_(res), lv_(lv), rv_(rv)
        {

        }
        ~AddGradOp() {

        }
        virtual int backward() {
            lv_.setGrad(generate(1, res_.shape()));
            rv_.setGrad(generate(1, res_.shape()));
            return 0;
        }
        virtual void reback() { lv_.reback(); rv_.reback(); }
        virtual std::vector<GradOp*> oplist() {
            return{ lv_.gop(),rv_.gop() };
        }
    private:
        std::string name_;
        tensor<RET> res_;
        tensor<LV> lv_;
        tensor<RV> rv_;
    };
    template<typename RET, typename LV, typename RV>
    class SubGradOp :public GradOp {
    public:
        SubGradOp() :name_("SubGradOp") {}
        SubGradOp(tensor<RET>& res, tensor<LV>& lv, tensor<RV>& rv)
            :name_("SubGradOp"), res_(res), lv_(lv), rv_(rv)
        {

        }
        ~SubGradOp() {

        }
        virtual int backward() {
            lv_.setGrad(generate(1, res_.shape()));
            rv_.setGrad(generate(-1, res_.shape()));
            return 0;
        }
        virtual void reback() { lv_.reback(); rv_.reback(); }
        virtual std::vector<GradOp*> oplist() {
            return{ lv_.gop(),rv_.gop() };
        }
    private:
        std::string name_;
        tensor<RET> res_;
        tensor<LV> lv_;
        tensor<RV> rv_;
    };
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
        virtual void reback() { lv_.reback(); rv_.reback();}
        virtual std::vector<GradOp*> oplist() {
            return{ lv_.gop(),rv_.gop() };
        }
    private:
        std::string name_;
        tensor<RET> res_;
        tensor<LV> lv_;
        tensor<RV> rv_;
    };
    template<typename RET, typename LV, typename RV>
    class DivGradOp :public GradOp {
    public:
        DivGradOp() :name_("DivGradOp") {}
        DivGradOp(tensor<RET>& res, tensor<LV>& lv, tensor<RV>& rv)
            :name_("DivGradOp"), res_(res), lv_(lv), rv_(rv)
        {

        }
        ~DivGradOp() {

        }
        virtual int backward() {
            lv_.setGrad(res_.grad()/rv_);
            //rv_.setGrad(res_.grad()*lv_);
            return 0;
        }
        virtual void reback() { lv_.reback(); rv_.reback(); }
        virtual std::vector<GradOp*> oplist() {
            return{ lv_.gop(),rv_.gop() };
        }
    private:
        std::string name_;
        tensor<RET> res_;
        tensor<LV> lv_;
        tensor<RV> rv_;
    };
}
#endif