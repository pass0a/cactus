#ifndef CACTUS_LAYER_HPP
#define CACTUS_LAYER_HPP

#include "../cactus/core/framework/tensor.h"

namespace cactus {
    template<typename T,typename Container = Tensor<T>>
    class layer {
        using shape_type = Container::shape_type;
    protected:
        Container weights_;
        Container bias_;
        shape_type in_shape_;
        shape_type out_shape_;
    };
}

#endif