#ifndef CACTUS_TENSOR_HPP
#define CACTUS_TENSOR_HPP

#include "../../xtensor/xarray.hpp"

namespace cactus {
    template <typename T = float_t>
    class Tensor
        :public xt::xarray<T> {
    public:
        Tensor() {

        }
        Tensor(shape_type sp)
            :xt::xarray<T>(sp) {

        }
        Tensor(container_type& buf,shape_type sp)
            :xt::xarray<T>(buf,sp) {
            
        }
        /*const shape_type shape() const { return storage_.shape(); }
        const size_type dim() const { return storage_.dim(); }
        const size_type size() const { return storage_.size(); }
        view_type operator [](size_t index) {
            return storage_[index];
        }
        reference ref(shape_type sp) {
            return storage_.ref(sp);
        }*/
    };

}
#endif