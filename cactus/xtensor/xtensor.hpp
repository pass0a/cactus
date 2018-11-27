#ifndef CACTUS_XTENSOR_HPP
#define CACTUS_XTENSOR_HPP

#include "xstorage.hpp"
#include <numeric>
#include <vector>
#include <iostream>

namespace xt {
    typedef std::vector<size_t> Shape;
    template <typename T=float_t,typename Storage=uvector<T>>
    class xtensor {
    public:
        xtensor() {
            
        }
        xtensor(T* buf,Shape sp)
            :shape_(sp), storage_(buf, std::accumulate(sp.begin(), sp.end(), (size_t)1, std::multiplies<size_t>())){
            
        }
        const Shape& shape() const { return shape_; }
        const size_t dim() const { return shape_.size(); }
        const size_t size() const { return storage_.size(); }
        xtensor operator [](size_t index) {
            T* p=storage_.data();
            size_t pos=index*storage_.size() / shape_[0];
            return xtensor();
        }
    private:
        Storage storage_;
        Shape shape_;
    };
}

#endif