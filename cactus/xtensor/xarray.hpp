#ifndef CACTUS_XARRAY_HPP
#define CACTUS_XARRAY_HPP

#include <vector>
#include <numeric>
#include "xview.hpp"

namespace xt {
    template<typename T,typename Container = std::vector<T>>
    class xarray{
    public:
        using shape_type = typename std::vector<size_t>;
        using container_type = typename Container ;
        using size_type = typename Container::size_type;
        using value_type = typename Container::value_type;
        using iterator = typename Container::iterator;
        using const_iterator = typename Container::const_iterator;
        using view_type = typename xview<xarray>;
        using reference = typename Container::reference;
        using pointer = typename Container::pointer;
        xarray()
            :shape_({ 0 }), data_(0), view(*this, 0, {0}) {}
        xarray(shape_type sp)
            :shape_(sp), data_(product(sp)), view(*this,0, sp){
        }
        xarray(container_type& rhs,shape_type sp)
            :shape_(sp),view(*this,0,sp) {
            data_ = std::move(rhs);
        }
        container_type& data() {
            return data_;
        }
        const size_type size() const {
            return data_.size();
        }
        const size_type dim() const {
            return shape_.size();
        }
        const shape_type shape() const {
            return shape_;
        }
        view_type operator [](size_t index) {
            return view[index];
        }
        reference ref(shape_type sp) {
            return view.ref(std::move(sp));
            
        }
    private:
        size_t product(shape_type& tmp) {
            size_t val=1;
            for (auto v : tmp) {
                val*=v;
            }
            return val;
        }
    private:
        container_type data_;
        shape_type shape_;
        view_type view;
    };
}

#endif