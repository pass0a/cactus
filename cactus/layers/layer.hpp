#ifndef CACTUS_LAYER_HPP
#define CACTUS_LAYER_HPP

#include "../cactus/core/framework/tensor.h"

namespace cactus {
    template<typename T,typename Backend, typename Container = tensor<T>>
    class layer {
    public:
        using shape_type =typename Container::shape_type;
    public:
        void weight_init(typename Container val) {
            bk_.weights_init(weights_,val);
        }
        void bias_init(typename Container val) {
            bk_.bias_init(weights_,val);
        }
        layer(shape_type inshape,shape_type outshape) 
            :in_shape_(inshape), out_shape_(outshape) {
            weights_.reshape({ outshape[0] ,inshape[0] + 1 });
        }
    protected:
        Container weights_;
        shape_type in_shape_;
        shape_type out_shape_;
        Backend bk_;
    };
}

#endif