#ifndef CACTUS_XSCALAR_HPP
#define CACTUS_XSCALAR_HPP

namespace xt {
    template<typename Storage>
    class xscalar {
    public:
        using comput_type = typename Storage::comput_type;
        using xranges = typename comput_type::xranges;
        using container_type = typename Storage::container_type;
        using out_type = typename Storage::out_type;
        using shape_type = typename Storage::shape_type;
        using size_type = typename Storage::size_type;
        using value_type = typename Storage::value_type;
        using iterator = typename Storage::iterator;
        using pointer = typename Storage::pointer;
        using reference = typename Storage::reference;
        xscalar(value_type val):data_(val) {
        }
        value_type value() {
            return data_;
        }
        value_type data_;
    };
}

#endif