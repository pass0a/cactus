
/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_BUFFER_HPP_
#define SRC_BUFFER_HPP_

#include "types.h"

namespace cactus {

    class BufferImpl;
    class Buffer {
    public:
        Buffer();
        explicit Buffer(uint32_t size);
        ~Buffer();
    public:
        uint32_t size() const;
        int resize(uint32_t size);
        void* data() const;
    private:
        /*std::shared_ptr<void> buf_;
        uint32_t size_;*/
        BufferImpl* impl;
    };
}  // namespace cactus

#endif  // SRC_BUFFER_HPP_
