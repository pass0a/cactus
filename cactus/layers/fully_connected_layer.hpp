#ifndef CACTUS_LAYER_FULL_CONNECTED_HPP
#define CACTUS_LAYER_FULL_CONNECTED_HPP
#include "layer.hpp"
namespace cactus {
    template<typename Backend,typename T = float>
    class fully_connected_layer :public layer<T,Backend> {
    public:
        
        fully_connected_layer(size_t inshape,size_t outshape)
            :layer({ inshape }, { outshape }) {
            
        }
        void forward(tensor<T> inputs, tensor<T>& outputs) {
            bk_.full_connect(inputs, weights_,outputs);
        }

    };
}

#endif