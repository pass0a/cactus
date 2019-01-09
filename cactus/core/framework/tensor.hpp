#ifndef CACTUS_TENSOR_HPP
#define CACTUS_TENSOR_HPP

//#ifdef USE_EIGEN3
//#else
//#include "../../util/eigen3.hpp"
//#endif

#include "../../xtensor/xarray.hpp"

namespace cactus {
    class NoneGradOp {
    public:
        NoneGradOp():name_("NoneGradOp"){}
        template<typename T>
        int operator()(T ) {
            return 0;
        }
        std::string name_;
    };
    template <
        typename T = float_t,
        typename GradOp=NoneGradOp,
        typename Storage = xt::xarray<T>>
    class tensor {
    public:
        using value_type = typename T;
        using shape_type = typename Storage::shape_type;
        using container_type = typename Storage::container_type;
        using view_type = typename Storage::view_type;
        using size_type = typename Storage::size_type;
        using reference = typename Storage::reference;
        using pointer = typename Storage::pointer;
    public:
        tensor() :storage_(), grad_(1){
        }
        tensor(GradOp &op) :storage_(), grad_(1),gof_(op) {
        }
        tensor(Storage &s) :storage_(s), grad_(1) {
        }
        tensor(T val) :storage_(val), grad_(1) {
        }
        tensor(tensor& rhs) 
            :storage_(rhs.storage_),
            gof_(rhs.gof_),
            grad_(1) {

        }
        tensor(std::initializer_list<value_type> buf) 
            :storage_(buf),
            grad_(1) {}
        //tensor(container_type& buf, shape_type sp):storage_(buf,sp) {}
        //tensor(pointer buf, shape_type sp) :storage_(buf, sp) {}

        pointer data() {
            return storage_.data();
        }
        const size_type size() const {
            return storage_.size();
        }
        const size_type dim() const {
            return storage_.dim();
        }
        const shape_type shape() const {
            return storage_.shape();
        }
        void reshape(shape_type sp) {
            storage_.resize(view_type::product(sp));
            storage_.reshape(sp);
        }
        reference ref(shape_type sp) {
            return storage_.ref(std::move(sp));
        }
        view_type operator [](size_t idx) {
            return storage_[idx];
        }
        template<typename OP>
        tensor& operator =(tensor<T,OP>& rhs) {
            //if (this != &rhs) {
                storage_ = rhs.storage_;
                //gof_ = rhs.gof_;
                grad_ = rhs.grad_;
            //}
            return *this;
        }
        template<typename Type, typename GradOp>
        friend std::ostream & operator<<(std::ostream & os, tensor<Type, GradOp>& stu);
        void backward() {
            gof_(grad_);
        }
        void backward(tensor gd) {
            grad_ = gd.storage_;
            gof_(grad_);
        }
        /*void bindGrad(GradOp fp) {
            gof_ = std::move(fp);
        }*/
    public:
        tensor grad() {
            return grad_;
        }
    public:
        Storage storage_;
        Storage grad_;
        GradOp gof_;
    };

}
#endif