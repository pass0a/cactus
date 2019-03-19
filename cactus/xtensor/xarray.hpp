#ifndef CACTUS_XARRAY_HPP
#define CACTUS_XARRAY_HPP

#include <vector>
#include <numeric>
#include <memory>

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
        using reference = typename Container::reference;
        using pointer = typename Container::pointer;
        xarray()
            :data_(0), shape_({ 0 }) {}
        xarray(shape_type sp)
            :shape_(sp), data_(product(sp)) {
            //std::copy(rhs.begin(), rhs.end(), data_.begin());
        }
        xarray(xarray& rhs)
            :data_(rhs.data_)
            shape_(rhs.shape()) {
        }
        xarray(T rhs)
            :shape_({1}), data_(1) {
            data_.at(0)=rhs;
        }
        xarray(container_type& rhs,shape_type sp)
            :data_(rhs)
            ,shape_(sp) {
            //*data_ = std::move(rhs);
        }
        xarray(pointer rhs, shape_type sp)
            :data_(view_type::product(sp))
            ,shape_(sp) {
            memcpy(data_.data(),rhs,data_.size());
        }
        pointer data() {
            return data_.data();
        }
        void clear() {
            data_.clear();
        }
        void fill(T val) {
            std::fill(data_.begin(),data_.end(),val);
        }
        const size_type size() const {
            return data_.size();
        }
        void resize(size_type len) {
            data_.resize(len);
        }
        const size_type dim() const {
            return shape_.size();
        }
        const shape_type shape() const {
            return shape_;
        }
        void reshape(shape_type sp) {
            resize(product(sp));
            shape_=sp;
        }
        /*view_type operator [](size_t index) {
            return view_[index];
        }*/
        xarray& operator =(xarray& rhs) {
            this->resize(rhs.size());
            this->reshape(rhs.shape());
            std::copy(rhs.begin(), rhs.end(), data_.begin());
            return *this;
        }
        xarray& operator =(std::initializer_list<T>& rhs) {
            if (rhs.size() > data_.size()) {
                std::copy(rhs.begin(), rhs.begin()+rhs.size(), data_.begin());
            }
            else {
                std::copy(rhs.begin(), rhs.end(), data_.begin());
            }
            return *this;
        }
        /*reference ref(shape_type sp) {
            return view_.ref(std::move(sp));
            
        }*/
        /*iterator begin() {
            return data_.begin();
        }
        iterator end() {
            return data_.end();
        }*/
        static size_t product(shape_type& tmp) {
            size_t val = 1;
            for (auto v : tmp) {
                val *= v;
            }
            return val;
        }
    protected:
        container_type data_;
        shape_type shape_;
    };
}

#endif