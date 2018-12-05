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
        template<typename Backend>
        void forward(tensor<T> inputs, tensor<T> outputs, Backend& bk) {
            bk.matmul(inputs, weights_);
        }

    };
}

#endif