#ifndef CACTUS_EIGEN3_HPP
#define CACTUS_EIGEN3_HPP

#include "common.hpp"
#include "operator.hpp"
namespace cactus {
template <typename T, typename S>
std::ostream &operator<<( std::ostream &os, tensor<T, S> stu ) {
    os << stu.value();
    return os;
}
} // namespace cactus
#endif
