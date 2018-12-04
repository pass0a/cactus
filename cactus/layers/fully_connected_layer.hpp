#ifndef CACTUS_LAYER_FULL_CONNECTED_HPP
#define CACTUS_LAYER_FULL_CONNECTED_HPP

#include "layer.hpp"
namespace cactus {
    template<typename T = float>
    class fully_connected_layer :public layer<T> {
    public:
        fully_connected_layer(shape_type inshape,shape_type outshape)
            :layer(inshape, outshape) {

        }
        void forward(tensor<T> inputs, tensor<T> outputs) {
            layer_matmul(inputs,this->weights_);
        }

    };
}

#endif