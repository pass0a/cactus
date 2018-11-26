#ifndef SRC_TENSOR_HPP_
#define SRC_TENSOR_HPP_

#include <vector>
namespace cactus {
    template<typename data_type>
    class scalar {};
    template<typename data_type>
    class Tensor {
    public:
        Tensor();
        Tensor(std::vector<size_t> shape) {}
        void* data() const;
        const Shape& shape() const;
        data_type& at(uint32_t pos) const {
            if (buf_.size()>pos) {
                return ((T*)data())[pos];
            }
            return T(0);
        }
    private:
        std::vector<data_type> buf_;
        Shape shape_;
    };

}

#endif  // SRC_TENSOR_HPP_
