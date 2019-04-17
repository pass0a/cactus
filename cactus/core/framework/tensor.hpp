#ifndef CACTUS_TENSOR_HPP
#define CACTUS_TENSOR_HPP

#include "../../xtensor/xarray.hpp"
#include "../../xtensor/xscalar.hpp"
#include "../../xtensor/xview.hpp"
#include "../operator/gradop.hpp"
#include <memory>
#include <queue>

namespace cactus {
template <typename T, typename Storage> class tensor {
  public:
    using value_type = T;
    using shape_type = typename Storage::shape_type;
    // using container_type = typename Storage::container_type;
    using size_type = typename Storage::size_type;
    using reference = typename Storage::reference;
    using pointer   = typename Storage::pointer;
    using out_type  = typename Storage::out_type;
    using xranges   = typename xt::xview<Storage>::xranges;
    using iterator  = typename Storage::iterator;

  public:
    tensor()
        : storage_() {}
    tensor( const Storage &s )
        : storage_( s ) {}
    tensor( const tensor &rhs )
        : storage_( rhs.storage_ ) {}
    explicit tensor( std::initializer_list<size_t> shape )
        : storage_( shape ) {}
    explicit tensor( shape_type shape )
        : storage_( shape ) {}
    explicit tensor( T val )
        : storage_( val ) {}

    decltype( auto ) subView( xranges xrgs ) {
        tensor<T, xt::xview<Storage>> tmp(
            xt::xview<Storage>( storage_, xrgs ) );
        return tmp;
    }
    decltype( auto ) value() { return storage_.value(); }
    pointer          data() { return storage_.data(); }
    const size_type  dim() const { return storage_.dim(); }
    const shape_type shape() const { return storage_.shape(); }
    void             reshape( shape_type sp ) {
        // storage_.resize(xt::xview<Storage>::product(sp));
        storage_.reshape( sp );
    }
    reference ref( shape_type sp ) { return storage_.ref( std::move( sp ) ); }
    size_t    size() { return storage_.size(); }
    /*view_type operator [](size_t idx) {
          return (*storage_)[idx];
      }*/
    // template<typename Type,typename Storage>
    // tensor& operator =(tensor<Type, xt::xview<Storage>>& rhs) {
    //    /*if (this != &rhs) {
    //        storage_ = rhs.storage_;
    //    }*/
    //    return *this;
    //}
    template <typename Type, typename TS>
    tensor &operator=( tensor<Type, TS> &rhs ) {
        if ( !storage_.size() ) {
            storage_.reshape( rhs.shape() );
        }
        if ( std::is_same<T, Type>() ) {
            value() = rhs.value();
        }
        return *this;
    }
    tensor &operator=( std::initializer_list<T> rhs ) {
        if ( !storage_.size() ) {
            storage_.reshape( {rhs.size()} );
        }
        storage_ = rhs;
        return *this;
    }
    // void fill(T val) { storage_.fill(val); }
    iterator begin() { return storage_.begin(); }
    iterator end() { return storage_.end(); }

  private:
    Storage storage_;
};
/*template<typename T>
tensor<T> generate(T val,typename tensor<T>::shape_type st) {
    tensor<T> tmp;
    tmp.reshape(st);
    tmp.fill(val);
    return tmp;
}*/
} // namespace cactus
#endif
