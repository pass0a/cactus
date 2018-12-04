#ifndef CACTUS_LAYER_INPUT_HPP
#define CACTUS_LAYER_INPUT_HPP

#include "layer.hpp"
namespace cactus {
    template<typename T = float>
    class input_layer :public layer<T> {
    public:
        input_layer(shape_type ins)
            :layer(ins,ins) {
          
        }
        void forward(tensor<T> inputs,tensor<T> outputs) {
            outputs = inputs;
        }
        
    };
}

#endif