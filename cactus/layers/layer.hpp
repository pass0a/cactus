#ifndef CACTUS_LAYER_HPP
#define CACTUS_LAYER_HPP
#include "../backend.hpp"
#include "../cactus/core/framework/tensor.h"

namespace cactus {
    template<typename T,typename Container = tensor<T>>
    class layer {
    public:
        using shape_type =typename Container::shape_type;
    public:
        void weight_init(typename Container val) {
            weights_ = val;
        }
        layer(shape_type inshape,shape_type outshape) 
            :in_shape_(inshape),out_shape_(outshape){}
    protected:
        Container weights_;
        Container bias_;
        shape_type in_shape_;
        shape_type out_shape_;
    };
}

#endif