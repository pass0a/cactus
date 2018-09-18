
/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_BUFFER_HPP_
#define SRC_BUFFER_HPP_

#include <cassert>
#include <stdint.h>
#include <memory>

namespace cactus {

class Buffer {
 public:
    Buffer():buf_(0),size_(0) {
    }
    explicit Buffer(uint32_t size):buf_(0) {
        resize(size);
    }
    ~Buffer() {
        
    }

 public:
    uint32_t size() const {
        return size_;
    }
    int resize(uint32_t size) {
        if (buf_.get()) {
            buf_.reset(std::realloc(buf_.get(), size),std::free);
        } else {
            buf_.reset(std::malloc(size), std::free);
        }
        size_ = size;
        assert(buf_.get() != NULL);
        return 0;
    }
    void* data() const {
        return buf_.get();
    }
 private:
    std::shared_ptr<void> buf_;
    uint32_t size_;
};
}  // namespace cactus

#endif  // SRC_BUFFER_HPP_
