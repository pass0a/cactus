/*
    Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_OPS_HPP_
#define SRC_OPS_HPP_

#include "tensor.hpp"

namespace cactus {
    struct Initalizer {
        template<typename T>
        Initalizer(const std::initializer_list<T>& v) {
            Shape s={ v.size(),1 };
            t = Tensor(DataTypeToEnum<T>::value,s);
            std::copy_n(v.begin(), v.size(), (char*)t.data());
        }
        Initalizer(const std::initializer_list<Initalizer>& v) {
            uint32_t offset=0;
            auto const & first = *v.begin();
            first.tensor.dtype();
            //Shape s={  , v.size() };
            //t = Tensor(t.dType(),s);
            //for (auto n:v){
            //    std::cout << n.tensor().dType() << std::endl;
            //    //std::copy_n((char*)n.tensor().data(),n.t.TotalBytes(),(char*)t.data());
            //}
        }
        Tensor tensor;
    };
    /*class Input {
    public:
        
    };
    class InputList {
    public:
        InputList(const std::initializer_list<Input>& v) :l(v.begin(), v.end()) {
        }
    private:
        std::vector<Input> l;
    };*/
    int Const(const Initalizer& v) {
        //auto t = v;
        //std::cout << t.tensor().TotalBytes() << std::endl;
        return 0;
    }
}

#endif  // SRC_TENSOR_HPP_
