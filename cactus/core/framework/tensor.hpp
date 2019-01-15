#ifndef CACTUS_TENSOR_HPP
#define CACTUS_TENSOR_HPP

//#ifdef USE_EIGEN3
//#else
//#include "../../util/eigen3.hpp"
//#endif

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
    template<typename T>
    class NoneGradOp:public GradOp {
    public:
        NoneGradOp()
            :name_("NoneGradOp")
            {}
        virtual int backward() {
            return 0;
        }
        virtual std::vector<GradOp*> oplist() {
            return { };
        }
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
            using view_type = typename Storage::view_type;
            using size_type = typename Storage::size_type;
            using reference = typename Storage::reference;
            using pointer = typename Storage::pointer;
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
            tensor(std::initializer_list<value_type> buf)
                :storage_(std::make_shared<Storage>(buf)),
                grad_(std::make_shared<GradType>()),
                gop_(std::make_shared<NoneGradOp<T>>()) {}
            //tensor(container_type& buf, shape_type sp):storage_(buf,sp) {}
            //tensor(pointer buf, shape_type sp) :storage_(buf, sp) {}

            pointer data() {
                return storage_->data();
            }
            const size_type size() const {
                return storage_->size();
            }
            const size_type dim() const {
                return storage_->dim();
            }
            const shape_type shape() const {
                return storage_->shape();
            }
            void reshape(shape_type sp) {
                storage_->resize(view_type::product(sp));
                storage_->reshape(sp);
            }
            reference ref(shape_type sp) {
                return storage_->ref(std::move(sp));
            }
            view_type operator [](size_t idx) {
                return (*storage_)[idx];
            }
            tensor& operator =(const tensor& rhs) {
                if (this != &rhs) {
                    *storage_ = *rhs.storage_;
                    *grad_ = *rhs.grad_;
                    gop_ = rhs.gop_;
                }
                return *this;
            }
            template<typename Type, typename GradOp>
            friend std::ostream & operator<<(std::ostream & os, tensor<Type, GradOp>& stu);
            void backward() {
                tensor<float> tmp(grad_);
                tmp.reshape({ 1 });
                tmp.ref({ 0 }) = 1;

                GradOp* ptr = gop_.get();
                std::vector<GradOp*> list,opl;
                std::queue<GradOp*> queue;
                list.emplace_back(ptr);
                while (ptr)
                {
                    opl = ptr->oplist();
                    for (auto it:opl)
                    {
                        queue.emplace(it);
                    }
                    list.insert(list.end(), opl.begin(), opl.end());
                    if (queue.empty()) {
                        ptr = NULL;
                    }else{
                        ptr = queue.front();
                        queue.pop();
                    }
                }
                for (auto it:list) {
                    it->backward();
                }
            }
            void backward(tensor<float> gd) {
                tensor<float> tmp(grad_);
                tmp = gd;
                gop_->backward();
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
            void setGrad(tensor<float> gd) {
                tensor<float> tmp(grad_);
                if (tmp.size()) {
                    tmp =tmp+ gd;
                }
                else {
                    tmp = gd;
                }
            }
            GradOp* gop() {
                return gop_.get();
            }
    private:
        std::shared_ptr<Storage> storage_;
        std::shared_ptr<GradType> grad_;
        std::shared_ptr<GradOp> gop_;
    };

}
#endif