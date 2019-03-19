#ifndef CACTUS_TENSOR_HPP
#define CACTUS_TENSOR_HPP


#include "../../xtensor/xarray.hpp"
#include "../operator/gradop.hpp"
#include <queue>

namespace cactus {
    
    template <
        typename T = float,
        typename Storage = xt::xarray<T>,
        typename GradType = xt::xarray<float>>
    class tensor;
    template<typename Tx, typename Ty>
    tensor<Ty> tensor_cast(tensor<Tx> in);
    template<typename RET, typename LV=void, typename RV=void>
    class NoneGradOp:public GradOp {
    public:
        NoneGradOp()
            :name_("NoneGradOp")
            {}
        NoneGradOp(tensor<RET>& res, tensor<RET>& lv) {}
        NoneGradOp(tensor<RET>& res, tensor<LV>& lv, tensor<RV>& rv) {}
        virtual int backward() {
            return 0;
        }
        virtual std::vector<GradOp*> oplist() {
            return { };
        }
        virtual void reback() {}
        std::string name_;
    };
    template <
        typename T,
        typename Storage,
        typename GradType>
        class tensor {
        public:
            using value_type = typename T;
            using shape_type = typename Storage::shape_type;
            using container_type = typename Storage::container_type;
            using size_type = typename Storage::size_type;
            using reference = typename Storage::reference;
            using pointer = typename Storage::pointer;
            //using xranges = typename xt::xview<Storage>::xranges;
        public:
            tensor()
                :storage_(std::make_shared<Storage>()),
                grad_(std::make_shared<GradType>()),
                gop_(std::make_shared<NoneGradOp<T>>()) {
            }
            tensor(std::shared_ptr<GradOp> gop)
                :storage_(std::make_shared<Storage>()),
                grad_(std::make_shared<GradType>()),
                gop_(gop) {
            }
            tensor(std::shared_ptr<Storage> &s)
                :storage_(s),
                grad_(std::make_shared<GradType>()),
                gop_(std::make_shared<NoneGradOp<T>>()) {
            }
            tensor(T val)
                :storage_(std::make_shared<Storage>(val)),
                grad_(std::make_shared<GradType>()),
                gop_(std::make_shared<NoneGradOp<T>>()) {
            }
            tensor(tensor& rhs)
                :storage_(rhs.storage_),
                grad_(rhs.grad_),
                gop_(rhs.gop_)
            {
            }
            /*tensor(tensor& rhs, std::vector<xt::xrange> lists)
                : storage_(rhs.storage_),
                grad_(std::make_shared<GradType>()),
                gop_(std::make_shared<NoneGradOp<T>>())
            {
            }*/
            tensor(shape_type shape)
                :storage_(std::make_shared<Storage>(shape)),
                grad_(std::make_shared<GradType>()),
                gop_(std::make_shared<NoneGradOp<T>>()) {}
            //tensor(container_type& buf, shape_type sp):storage_(buf,sp) {}
            //tensor(pointer buf, shape_type sp) :storage_(buf, sp) {}
            /*const xranges range() const {
                return view_.range();
            }*/
            pointer data() {
                return storage_->data();
            }
            const size_type dim() const {
                return storage_->dim();
            }
            const shape_type shape() const {
                return storage_->shape();
            }
            auto array() {
                T2V<T> x;
                shape_type sh = shape();
                return x.array(data(), sh[0], sh[1]);
            }
            void reshape(shape_type sp) {
                //storage_->resize(xt::xview<Storage>::product(sp));
                storage_->reshape(sp);
            }
            reference ref(shape_type sp) {
                return storage_->ref(std::move(sp));
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
                *storage_ = rhs;
                return *this;
            }
            template<typename Type, typename GradOp>
            friend std::ostream & operator<<(std::ostream & os, tensor<Type, GradOp>& stu);
            void backward_impl() {
                GradOp* ptr = gop_.get();
                std::vector<GradOp*> list, opl;
                std::queue<GradOp*> queue;
                list.emplace_back(ptr);
                while (ptr)
                {
                    opl = ptr->oplist();
                    for (auto it : opl)
                    {
                        queue.emplace(it);
                    }
                    list.insert(list.end(), opl.begin(), opl.end());
                    if (queue.empty()) {
                        ptr = NULL;
                    }
                    else {
                        ptr = queue.front();
                        queue.pop();
                    }
                }
                for (auto it : list) {
                    it->reback();
                }
                for (auto it : list) {
                    it->backward();
                }
            }
            void backward() {
                tensor<float> tmp(grad_);
                tmp.reshape({ 1 });
                tmp.ref({ 0 }) = 1;

                backward_impl();
            }
            void backward(tensor<float> gd) {
                tensor<float> tmp(grad_);
                tmp = gd;
                backward_impl();
            }
            
            tensor<float> grad() {
                return tensor<float>(grad_);
            }
            void bindOp(std::shared_ptr<GradOp> gop) {
                gop_ = gop;
            }
            template<typename Type>
            tensor<Type> cast() {
                return tensor_cast<T,Type>(*this);
            }
            void reback() {
                grad_->clear();
            }
            template<typename Type>
            void setGrad(tensor<Type> gd) {
                /*tensor<float> tmp(grad_);
                if (tmp.size()) {
                    tmp.assign(tmp+ gd.cast<float>());
                }
                else {
                    tmp.assign(gd.cast<float>());
                }*/
            }
            GradOp* gop() {
                return gop_.get();
            }
            void fill(T val) {
                storage_->fill(val);
            }
            void assign(tensor& rhs) {
                *storage_ = *rhs.storage_;
                *grad_ = *rhs.grad_;
            }
    private:
        std::shared_ptr<Storage> storage_;
        std::shared_ptr<GradType> grad_;
        std::shared_ptr<GradOp> gop_;
    };
    template<typename T>
    tensor<T> generate(T val,typename tensor<T>::shape_type st) {
        tensor<T> tmp;
        tmp.reshape(st);
        tmp.fill(val);
        return tmp;
    }
}
#endif