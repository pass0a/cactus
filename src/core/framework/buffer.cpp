#include "buffer.hpp"
#include <memory>

namespace cactus {
    class BufferImpl {
    public:
        BufferImpl() :buf_(0), size_(0) {}
        BufferImpl(uint32_t& size) :buf_(0) {
            resize(size);
        }
        uint32_t size() const {
            return size_;
        }
        void* data() const {
            return buf_.get();
        }
        int resize(uint32_t size) {
            buf_.reset(std::malloc(size), std::free);
            size_ = size;
            assert(buf_.get() != NULL);
            return 0;
        }
    private:
        std::shared_ptr<void> buf_;
        uint32_t size_;
    };
    Buffer::Buffer() :impl(new BufferImpl()) {
    }
    Buffer::Buffer(uint32_t size) : impl(new BufferImpl(size)) {
    }
    Buffer::~Buffer() {

    }
    uint32_t Buffer::size() const {
        return impl->size();
    }
    int Buffer::resize(uint32_t size) {
        impl->resize(size);
        return 0;
    }
    void* Buffer::data() const {
        return impl->data();
    }

}  // namespace cactus