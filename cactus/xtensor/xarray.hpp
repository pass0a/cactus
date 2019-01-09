#ifndef CACTUS_XARRAY_HPP
#define CACTUS_XARRAY_HPP

#include <vector>
#include <numeric>
#include "xview.hpp"
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
        using view_type = typename xview<xarray>;
        using reference = typename Container::reference;
        using pointer = typename Container::pointer;
        xarray()
            :data_(std::make_shared<container_type>(0)), view_(*this, 0, {0}) {}
        xarray(std::initializer_list<value_type>& rhs)
            :view_(*this, 0, { rhs.size() }) {
            data_ = std::make_shared<container_type>(rhs.size());
            std::copy(rhs.begin(), rhs.end(), data_->begin());
            /*for ( auto v:rhs)
            {
                data_->push_back(v);
            }*/
            //data_=(std::move(rhs));
        }
        xarray(xarray& rhs)
            :data_(rhs.data_),
            view_(*this, 0, rhs.shape()) {
        }
        xarray(T rhs)
            :view_(*this, 0, {1}) {
            data_ = std::make_shared<container_type>(1);
            data_->at(0)=rhs;
        }
        xarray(container_type& rhs,shape_type sp)
            :data_(std::make_shared<container_type>(rhs)),
            view_(*this,0,sp) {
            //*data_ = std::move(rhs);
        }
        xarray(pointer rhs, shape_type sp)
            :data_(std::make_shared<container_type>(view_type::product(sp))),
            view_(*this, 0, sp) {
            memcpy(data_->data(),rhs,data_->size());
        }
        pointer data() {
            return data_->data();
        }
        const size_type size() const {
            return data_->size();
        }
        void resize(size_type len) {
            data_->resize(len);
        }
        const size_type dim() const {
            return view_.dim();
        }
        const shape_type shape() const {
            return view_.shape();
        }
        void reshape(shape_type sp) {
            return view_.reshape(sp);
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
            return data_->begin();
        }
        iterator end() {
            return data_->begin();
        }
    protected:
        std::shared_ptr<container_type> data_;
        view_type view_;
    };
}

#endif