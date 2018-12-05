#ifndef CACTUS_TENSOR_HPP
#define CACTUS_TENSOR_HPP

#include "../../xtensor/xarray.hpp"

namespace cactus {
    template <typename T = float_t,typename Storage= xt::xarray<T>>
    class tensor{
    public:
        using value_type = typename T;
        using shape_type = typename Storage::shape_type;
        using container_type = typename Storage::container_type;
        using view_type = typename Storage::view_type;
        using size_type = typename Storage::size_type;
        using reference = typename Storage::reference;
        using pointer = typename Storage::pointer;
    public:
        tensor() {}
        tensor(shape_type sp):storage_(sp) {}
        tensor(container_type buf,shape_type sp):storage_(buf,sp) {}
        
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
        reference ref(shape_type sp) {
            return storage_.ref(std::move(sp));
        }
        view_type operator [](size_t idx) {
            return storage_[idx];
        }
        tensor& operator =(tensor& rhs) {
            storage_ = rhs.storage_;
            return *this;
        }
    private:
        Storage storage_;
    };

}
#endif