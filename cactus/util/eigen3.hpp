#ifndef CACTUS_EIGEN3_HPP
#define CACTUS_EIGEN3_HPP

#include "../3rd/eigen/Eigen/Dense"
#include "../core/framework/tensor.hpp"

namespace cactus {
#define arithmetic_eigen(val,lv,rv,opt) if (lv.size() == rv.size()) {\
    val.reshape(lv.shape());\
    Map<Array<LV, Dynamic, RowMajor>>\
        x(lv.data(), lv.size()), y(rv.data(), rv.size()), z(val.data(), val.size());\
    z = x opt y;\
    }\
else if (lv.size() == 1) {\
    val.reshape(rv.shape());\
    Map<Array<LV, Dynamic, RowMajor>>\
        y(rv.data(), rv.size()), z(val.data(), val.size());\
    z = lv.ref({ 0 }) opt y;\
}\
else if (rv.size() == 1) {\
    val.reshape(lv.shape());\
    Map<Array<LV, Dynamic, RowMajor>>\
        x(lv.data(), lv.size()), y(rv.data(), rv.size()), z(val.data(), val.size());\
    z = x opt rv.ref({ 0 });\
}
    using namespace Eigen;
    template<typename LV, typename RV>
    class AddGradOp{
    public:
        AddGradOp() {}
        //AddGradOp(AddGradOp& v) :lv_(v.lv_), rv_(v.rv_) {}
        AddGradOp(tensor<LV> lv, tensor<RV> rv)
            :lv_(lv),rv_(rv) {
        }
        
        int operator()(tensor<LV> gd) {
            lv_.backward();
            rv_.backward();
            return 0;
        }
        std::string name = "AddGradOp";
    private:
        tensor<LV> lv_;
        tensor<RV> rv_;
    };
    template<typename LV,typename RV>
    tensor<LV, AddGradOp<LV, RV>> operator +(tensor<LV>& lv, tensor<RV>& rv) {
        tensor<LV,AddGradOp<LV,RV>> val;
        val.bindGrad(AddGradOp<LV, RV>(lv,rv));
        val.reshape(lv.shape());
        
        Map<Array<LV, Dynamic, RowMajor>>
            x(lv.data(),lv.size()),z(val.data(),val.size());
       
        if (rv.size() == 1) {
            z = x + rv.ref({ 0 });
        }
        else {
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = x + y.cast<LV>();
        }
        return val;
    }
    template<typename LV, typename RV>
    tensor<LV, AddGradOp<LV, RV>> operator +(tensor<LV>& lv, RV rv) {
        tensor<RV> val=rv;
        return lv+val;
    }
    
    template<typename LV, typename RV>
    class MulGradOp {
    public:
        MulGradOp() {}
        //AddGradOp(AddGradOp& v) :lv_(v.lv_), rv_(v.rv_) {}
        MulGradOp(tensor<LV> lv, tensor<RV> rv)
            :lv_(lv), rv_(rv) {
        }

        int operator()(tensor<LV> gd) {
            lv_.grad()= gd*rv_;
            lv_.backward();
            rv_.backward();
            return 0;
        }
        std::string name = "MulGradOp";
    private:
        tensor<LV> lv_;
        tensor<RV> rv_;
    };
    template<typename LV, typename RV>
    tensor<LV, MulGradOp<LV, RV>> operator *(tensor<LV>& lv, tensor<RV>& rv) {
        tensor<LV, MulGradOp<LV, RV>> val(MulGradOp<LV, RV>(lv, rv));
        arithmetic_eigen(val,lv,rv,*);
        return val;
    }
    
    template<typename LV, typename RV>
    tensor<LV, MulGradOp<LV, RV>> operator *(tensor<LV>& lv, RV rv) {
        tensor<RV> val = rv;
        return lv * val;
    }

    template<typename Type,typename GradOp>
    std::ostream & operator<<(std::ostream & os, tensor<Type, GradOp>& stu)
    {
        // TODO: 在此处插入 return 语句
        Map<Array<Type, Dynamic, RowMajor>>
            tmp(stu.data(), stu.size());
        os << tmp;
        return os;
    }
    
}
#endif