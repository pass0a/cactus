#ifndef CACTUS_EIGEN3_HPP
#define CACTUS_EIGEN3_HPP

#include "../3rd/eigen/Eigen/Dense"
#include "../core/framework/tensor.hpp"


namespace cactus {
    using namespace Eigen;

    //#define arithmetic_eigen(val,lv,rv,opt) 

        /*template<typename LV, typename OPL, typename RV, typename OPR>
        void setgrad(tensor<LV, OPL>& lv, tensor<RV, OPR>& rv) {
            if (lv.size()) {
                lv = lv+rv;
            }
            else {
                lv = rv;
            }
        }*/
    template<typename LV, typename RV>
    class AddGradOp :public GradOp {
    public:
        AddGradOp() :name_("AddGradOp") {}
        AddGradOp(tensor<LV>& res, tensor<LV>& lv, tensor<RV>& rv)
            :name_("AddGradOp"), res_(res), lv_(lv), rv_(rv)
        {

        }
        ~AddGradOp() {
        }
        virtual int backward() {
            //rv_.grad() = tensor<RV>(1)*1.0;
            return 0;
        }
    private:
        std::string name_;
        tensor<LV> res_;
        tensor<LV> lv_;
        tensor<RV> rv_;
    };
    template<typename LV, typename RV>
    tensor<LV> operator +(tensor<LV>& lv, tensor<RV>& rv) {
        tensor<LV> val;
        val.bindOp(std::make_shared<AddGradOp<LV, RV>>(val, lv, rv));
        if (lv.size() == rv.size()) {
            val.reshape(lv.shape());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size()), z(val.data(), val.size()); \
                Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = x + y.cast<LV>();
        }
        else if (lv.size() == 1) {
            val.reshape(rv.shape());
            Map<Array<LV, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = lv.ref({ 0 }) + y.cast<LV>();
        }
        else if (rv.size() == 1) {
            val.reshape(lv.shape());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size()), z(val.data(), val.size());
            z = x + rv.ref({ 0 });
        }
        return val;
    }
    template<typename LV, typename OPL, typename RV>
    tensor<LV, AddGradOp<LV, RV>> operator +(tensor<LV, OPL>& lv, RV rv) {
        tensor<RV, OPL> val = rv;
        return lv + val;
    }

    template<typename LV, typename RV>
    class MulGradOp :public GradOp {
    public:
        MulGradOp() :name_("AddGradOp") {}
        MulGradOp(tensor<LV>& res, tensor<LV>& lv, tensor<RV>& rv)
            :name_("AddGradOp"), res_(res), lv_(lv), rv_(rv)
        {

        }
        ~MulGradOp() {
            std::cout << "????" << std::endl;
        }
        virtual int backward() {
            //lv_.grad() = res_.grad()*rv_;
            //tensor<RV>(1)*1.0f;
            return 0;
        }
    private:
        std::string name_;
        tensor<LV> res_;
        tensor<LV> lv_;
        tensor<RV> rv_;
    };
    template<typename LV, typename RV>
    tensor<LV> operator *(tensor<LV>& lv, tensor<RV>& rv) {
        tensor<LV> val;
        val.bindOp(std::make_shared<MulGradOp<LV, RV>>(val, lv, rv));
        //arithmetic_eigen(val, lv, rv, *);
        std::is_same
        if (lv.size() == rv.size()) {

            val.reshape(lv.shape());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size()), z(val.data(), val.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = x * y.cast<LV>();
        }
        else if (lv.size() == 1) {

            val.reshape(rv.shape());
            Map<Array<LV, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = lv.ref({ 0 }) * y.cast<LV>();
        }
        else if (rv.size() == 1) {

            val.reshape(lv.shape());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size()), z(val.data(), val.size());
            z = x * rv.ref({ 0 });
        }
        return val;
    }

    template<typename LV, typename RV>
    tensor<LV> operator *(tensor<LV>& lv, RV rv) {
        tensor<RV> val = rv;
        return lv * val;
    }

    template<typename Type>
    std::ostream & operator<<(std::ostream & os, tensor<Type>& stu)
    {
        // TODO: 在此处插入 return 语句
        Map<Array<Type, Dynamic, RowMajor>>
            tmp(stu.data(), stu.size());
        os << tmp;
        return os;
    }

}
#endif