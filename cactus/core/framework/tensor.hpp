#ifndef CACTUS_TENSOR_HPP
#define CACTUS_TENSOR_HPP


#include "../../xtensor/xarray.hpp"
#include "../../xtensor/xview.hpp"
#include "../../xtensor/xscalar.hpp"
#include "../operator/gradop.hpp"
#include <queue>
#include <memory>

namespace cactus {
    template <
        typename T,
        typename Storage>
        class tensor {
        public:
            using value_type = typename T;
            using shape_type = typename Storage::shape_type;
            //using container_type = typename Storage::container_type;
            using size_type = typename Storage::size_type;
            using reference = typename Storage::reference;
            using pointer = typename Storage::pointer;
            using out_type = typename Storage::out_type;
            using xranges = typename xt::xview<Storage>::xranges;
        public:
            tensor()
                :storage_() {
            }
            tensor(Storage &s)
                :storage_(s) {
            }
            tensor(T val)
                :storage_(val) {
            }
            tensor(tensor& rhs)
                :storage_(rhs.storage_)
            {
            }
            
            /*tensor(Storage& s)
                : storage_(s)
            {
            }*/
            tensor(shape_type shape)
                :storage_(shape){}
            //tensor(container_type& buf, shape_type sp):storage_(buf,sp) {}
            //tensor(pointer buf, shape_type sp) :storage_(buf, sp) {}
            /*const xranges range() const {
                return view_.range();
            }*/
            tensor<T, xt::xview<Storage>> subView(xranges xrgs) {
                tensor<T, xt::xview<Storage>> tmp(xt::xview<Storage>(storage_,xrgs));
                return tmp;
            }
            decltype(auto) value() {
                return storage_.value();
            }
            pointer data() {
                return storage_.data();
            }
            const size_type dim() const {
                return storage_.dim();
            }
            const shape_type shape() const {
                return storage_.shape();
            }
            void reshape(shape_type sp) {
                //storage_.resize(xt::xview<Storage>::product(sp));
                storage_.reshape(sp);
            }
            reference ref(shape_type sp) {
                return storage_.ref(std::move(sp));
            }
            /*view_type operator [](size_t idx) {
                return (*storage_)[idx];
            }*/
            tensor& operator =(const tensor& rhs) {
                if (this != &rhs) {
                    storage_ = rhs.storage_;
                    grad_ = rhs.grad_;
                    gop_ = rhs.gop_;
                }
                return *this;
            }
            tensor& operator =(std::initializer_list<T> rhs) {
                storage_ = rhs;
                return *this;
            }
            /*
            template<typename Type, typename GradOp>
            friend std::ostream & operator<<(std::ostream & os, tensor<Type, GradOp>& stu);
            */
            void fill(T val) {
                storage_.fill(val);
            }
            void assign(tensor& rhs) {
                storage_ = rhs.storage_;
            }
    private:
        Storage storage_;
    };
    /*template<typename T>
    tensor<T> generate(T val,typename tensor<T>::shape_type st) {
        tensor<T> tmp;
        tmp.reshape(st);
        tmp.fill(val);
        return tmp;
    }*/
}
#endif