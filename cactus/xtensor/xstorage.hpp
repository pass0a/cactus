#ifndef CACTUS_XSTORAGE_HPP
#define CACTUS_XSTORAGE_HPP

#include <memory>

namespace xt {
    template <typename T>
    class uvector {
    public:
        uvector() noexcept
            : _buf(0),_size(0)
        {
            //assert(std::is_pod<T>::value);
        }
        uvector(T* buf,size_t sh) noexcept
            : _buf(0), _size(0)
        {
            //_size=std::accumulate(sh.begin(), sh.end(), (size_t)1, std::multiplies<size_t>());
            //assert(std::is_pod<T>::value);
            _size = sh;
            _buf = new T[_size];
            if (std::is_pod<T>::value) {
                memcpy(_buf, buf, _size);
            }
            else {
                for (size_t i = 0; i < sh;i++) {
                    _buf[i] = buf[i];
                }
            }
        }
        T* data() { return _buf; }
        ~uvector() { delete _buf; }
        size_t size() const noexcept {
            return _size;
        }
    private:
        T* _buf;
        size_t _size;
    };
}

#endif