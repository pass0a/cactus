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
            :data_(0), view_(*this, 0, {0}) {}
        xarray(shape_type sp)
            :data_(product(sp)), view_(*this,0, sp){
        }
        xarray(container_type& rhs,shape_type sp)
            :view_(*this,0,sp) {
            data_ = std::move(rhs);
        }
        pointer data() {
            return data_.data();
        }
        const size_type size() const {
            return data_.size();
        }
        const size_type dim() const {
            return view_.dim();
        }
        const shape_type shape() const {
            return view_.shape();
        }
        view_type operator [](size_t index) {
            return view_[index];
        }
        xarray& operator =(xarray rhs) {
            data_ = rhs.data_;
            view_.reshape(rhs.shape());
            return *this;
        }
        reference ref(shape_type sp) {
            return view_.ref(std::move(sp));
            
        }
        iterator begin() {
            return data_.begin();
        }
        iterator end() {
            return data_.begin();
        }
    private:
        size_t product(shape_type& tmp) {
            size_t val=1;
            for (auto v : tmp) {
                val*=v;
            }
            return val;
        }
    protected:
        container_type data_;
        view_type view_;
    };
}

#endif