#ifndef CACTUS_XVIEW_HPP
#define CACTUS_XVIEW_HPP

#include <assert.h>
#include <memory>
namespace xt {
    struct xrange {
        int start;
        int len;
    };
    template<typename Storage>
    class xview {
    public:
        using size_type = typename Storage::size_type;
        using shape_type = typename Storage::shape_type;
        using value_type = typename Storage::value_type;
        using iterator = typename Storage::iterator;
        using pointer = typename Storage::pointer;
        using const_iterator = typename Storage::const_iterator;
        using container_type = typename Storage::container_type;
        using reference = typename Storage::reference;
        using xranges = typename std::vector<xrange>;
        xview(Storage& storage)
            :storage_(storage)
            ,shape_(storage_.shape()){
            /*for (auto it : shape_) {
                range_.push_back({ 0, (int)it });
            }*/
        }
        xview(xview& xv, xranges range)
             :storage_(xv.storage_)
             ,range_(range)
             ,shape_() {
            xrange tmp;
            shape_type shape=xv.shape();
            for (size_t i = 0; i < shape.size(); i++)
            {
                tmp = range_.at(i);
                assert(tmp.start+tmp.len <= shape[i]);
                shape_.push_back(tmp.len);
            }
        }
        /*iterator begin() {
            return storage_.begin() + start_;
        }
        iterator end() {
            return storage_.begin() + start_+len_;
        }*/
        const xranges range() const {
            return range_;
        }
        pointer data() {
            return storage_.data();
        }
        const size_type size() const {
            return storage_.size();
        }
        const size_type dim() const {
            return shape_.size();
        }
        const shape_type shape() const {
            return shape_;
        }
        void reshape(shape_type sp) {
            shape_=sp;
        }
        xview operator [](size_t index) {
            assert(shape_.size() > 1);
            shape_type tmp = shape_;
            size_type len = size() / shape_[0];
            size_type start = index*len;
            tmp.erase(tmp.begin());
            return xview(storage_, start, tmp);
        }
        reference ref(shape_type sp) {
            assert(sp.size() <= shape_.size());
            size_t val = 0;
            shape_type tmp = shape_;
            for (size_t i = 0; i<sp.size(); i++)
            {
                assert(sp[i] < shape_[i]);
                tmp.erase(tmp.begin());
                val += sp[i] * view_type::product(tmp);
            }
            return storage_.data()[val];
        }
    private:
        Storage& storage_;
        xranges range_;
        shape_type shape_;
    };
    
}
#endif