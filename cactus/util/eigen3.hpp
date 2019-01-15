#ifndef CACTUS_EIGEN3_HPP
#define CACTUS_EIGEN3_HPP

#include "../3rd/eigen/Eigen/Dense"
#include "../core/framework/tensor.hpp"


namespace cactus {
    using namespace Eigen;
	template<typename Tx, typename Ty>
	struct S {
		auto operator()() { Tx x; Ty y; return x + y; }
	};

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
            lv_.setGrad(1);
            rv_.setGrad(1);
            return 0;
        }
        virtual std::vector<GradOp*> oplist() {
            return { lv_.gop(),rv_.gop() };
        }
    private:
        std::string name_;
        tensor<RET> res_;
        tensor<LV> lv_;
        tensor<RV> rv_;
    };
    template<typename LV, typename RV>
    tensor<typename std::result_of<S<LV, RV>()>::type> operator +(tensor<LV>& lv, tensor<RV>& rv) {
        using result_type = typename std::result_of<S<LV, RV>()>::type;
        tensor<result_type> val;
        val.bindOp(std::make_shared<AddGradOp<result_type, LV, RV>>(val, lv, rv));
        //arithmetic_eigen(val, lv, rv, *);
        if (lv.size() == rv.size()) {
            val.reshape(lv.shape());
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = x.cast<result_type>() + y.cast<result_type>();
        }
        else if (lv.size() == 1) {
            val.reshape(rv.shape());
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<RV, Dynamic, RowMajor>>
                y(rv.data(), rv.size());
            z = (result_type)lv.ref({ 0 }) + y.cast<result_type>();
        }
        else if (rv.size() == 1) {
            val.reshape(lv.shape());
            Map<Array<result_type, Dynamic, RowMajor>>
                z(val.data(), val.size());
            Map<Array<LV, Dynamic, RowMajor>>
                x(lv.data(), lv.size());
            z = x.cast<result_type>() + (result_type)rv.ref({ 0 });
        }
        return val;
    }
    template<typename LV, typename RV>
    tensor<typename std::result_of<S<LV, RV>()>::type> operator +(tensor<LV>& lv, RV rv) {
        tensor<RV> val = rv;
        return lv + val;
    }

    template<typename RET,typename LV, typename RV>
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
        val.bindOp(std::make_shared<MulGradOp<result_type,LV, RV>>(val, lv, rv));
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

    template<typename Type>
    std::ostream & operator<<(std::ostream & os, tensor<Type>& stu)
    {
        // TODO: 在此处插入 return 语句
        Map<Array<Type, Dynamic, RowMajor>>
            tmp(stu.data(), stu.size());
        os << tmp;
        return os;
    }
    template<typename Tx,typename Ty>
    tensor<Ty> tensor_cast(tensor<Tx> in) {
        tensor<Ty> val;
        /*if (std::is_same<Tx, Ty>()) {
        }
        else {
        }*/
        val.reshape(in.shape());
        Map<Array<Tx, Dynamic, RowMajor>>
            x(in.data(), in.size());
        Map<Array<Ty, Dynamic, RowMajor>>
            y(val.data(), val.size());
        y = x.cast<Ty>();
        
        return val;
    }

}
#endif