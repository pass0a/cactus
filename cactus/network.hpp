#ifndef CACTUS_NETWORK_HPP
#define CACTUS_NETWORK_HPP

#include "nodes.hpp"
#include <vector>

template<typename NetType>
class network {
public:
    network() {};
    template <typename Layer>
    friend network<sequential> &operator<<(network<sequential> &n, Layer &&l);
private:
    NetType net_;
};

template <typename Layer>
network<sequential> &operator<<(network<sequential> &n, Layer &&l) {
    n.net_.add(std::forward<Layer>(l));
    return n;
}
#endif