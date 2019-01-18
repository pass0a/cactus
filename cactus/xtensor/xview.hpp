#ifndef CACTUS_XVIEW_HPP
#define CACTUS_XVIEW_HPP

#include <assert.h>
namespace xt {
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

        xview(Storage& storage, size_type start, shape_type shape)
            :storage_(storage), start_(start), shape_(shape) {
            len_ = 1;
            for (auto v : shape_) {
                len_ *= v;
            }
        }
        iterator begin() {
            return storage_.begin() + start_;
        }
        iterator end() {
            return storage_.begin() + start_+len_;
        }
        pointer data() {
            return storage_.data()+start_;
        }
        const size_type size() const {
            return len_;
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
                val += sp[i] * product(tmp);
            }
            return storage_.data()[val];
        }
        static size_t product(shape_type& tmp) {
            size_t val = 1;
            for (auto v : tmp) {
                val *= v;
            }
            return val;
        }
    private:
        Storage& storage_;
        shape_type shape_;
        size_type start_;
        size_type len_;
    };
    
}
#endif