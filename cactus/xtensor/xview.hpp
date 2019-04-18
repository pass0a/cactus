#ifndef CACTUS_XVIEW_HPP
#define CACTUS_XVIEW_HPP

#include <assert.h>
#include <iostream>
#include <memory>
namespace xt {

template <typename Storage> class xview {
  public:
    using comput_type = typename Storage::comput_type;
    using xranges     = typename comput_type::xranges;
    using xrange      = typename comput_type::xrange;
    using out_type    = typename Storage::out_type;
    using shape_type  = typename Storage::shape_type;
    using size_type   = typename Storage::size_type;
    using value_type  = typename Storage::value_type;
    using iterator    = typename Storage::iterator;
    using pointer     = typename Storage::pointer;
    using reference   = typename Storage::reference;

    xview( Storage &storage, xranges range )
        : storage_( storage )
        , range_( range )
        , shape_() {
        xrange     tmp;
        shape_type shape = storage_.shape();
        for ( size_t i = 0; i < shape.size(); i++ ) {
            tmp = range_.at( i );
            assert( tmp.start + tmp.len <= shape[ i ] );
            shape_.push_back( tmp.len );
        }
    }
    decltype( auto ) value() {
        return comput_type::matrix( storage_.data(), storage_.shape(), range_ );
    }
    // pointer         data() { return storage_.data(); }
    // const size_type size() const { return storage_.size(); }
    const size_type dim() const { return shape_.size(); }
    void            reshape( shape_type sp ) {
        assert( 0 /*,"xt::xview's reshape is disable!!!"*/ );
    }
    const shape_type shape() const { return shape_; }
    xview            operator[]( size_t index ) {
        assert( shape_.size() > 1 );
        shape_type tmp   = shape_;
        size_type  len   = storage_.size() / shape_[ 0 ];
        size_type  start = index * len;
        tmp.erase( tmp.begin() );
        return xview( storage_, start, tmp );
    }
    reference ref( shape_type sp ) {
        /*assert(sp.size() <= shape_.size());
        size_t val = 0;
        shape_type tmp = shape_;
        for (size_t i = 0; i<sp.size(); i++)
        {
            assert(sp[i] < shape_[i]);
            tmp.erase(tmp.begin());
            val += sp[i] * view_type::product(tmp);
        }*/
        return storage_.data()[ 0 ];
    }

  private:
    Storage &  storage_;
    xranges    range_;
    shape_type shape_;
};

} // namespace xt
#endif
