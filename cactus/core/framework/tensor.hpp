#ifndef CACTUS_TENSOR_HPP
#define CACTUS_TENSOR_HPP

//#ifdef USE_EIGEN3
//#else
//#include "../../util/eigen3.hpp"
//#endif

#include "../../xtensor/xarray.hpp"
#include "../operator/gradop.hpp"

namespace cactus {
    template <
        typename T = float,
        typename Storage = xt::xarray<T>>
    class tensor;

    template<typename T>
    class NoneGradOp:public GradOp {
    public:
        NoneGradOp()
            :name_("NoneGradOp")
            {}
        virtual int backward() {
            return 0;
        }
        std::string name_;
    };
    template <
        typename T,
        typename Storage>
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
            tensor() :storage_(), gop_(std::make_shared<NoneGradOp<T>>()) {
            }
            tensor(std::shared_ptr<GradOp> gop) :storage_(), gop_(gop) {
            }
            tensor(Storage &s) :storage_(s), gop_(std::make_shared<NoneGradOp<T>>()) {
            }
            tensor(T val) :storage_(val), gop_(std::make_shared<NoneGradOp<T>>()) {
            }
            tensor(tensor& rhs)
                :storage_(rhs.storage_)
            {
                gop_ = rhs.gop_;
            }
            tensor(std::initializer_list<value_type> buf)
                :storage_(buf)
                , gop_(std::make_shared<NoneGradOp<T>>()) {}
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
            template<typename Type>
            tensor& operator =(tensor<Type>& rhs) {
                if (this != &rhs) {
                    storage_ = rhs.storage_;
                    gop_ = rhs.gop_;
                }
                return *this;
            }
            template<typename Type, typename GradOp>
            friend std::ostream & operator<<(std::ostream & os, tensor<Type, GradOp>& stu);
            void backward() {
                tensor tmp(grad_);
                tmp.reshape({1});
                tmp.ref({0}) = 1;
                gop_->backward();
            }
            void backward(tensor gd) {
                tensor tmp(grad_);
                tmp = gd;
                gop_->backward();
            }
            tensor grad() {
                return tensor(grad_);
            }
            void bindOp(std::shared_ptr<GradOp> gop) {
                gop_ = gop;
            }
    private:
        Storage storage_;
        Storage grad_;
        std::shared_ptr<GradOp> gop_;
    };

}
#endif