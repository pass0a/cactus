#ifndef CACTUS_BK_EIGEN_HPP
#define CACTUS_BK_EIGEN_HPP

#include "../3rd/eigen/Eigen/Dense"
#include <cstdarg>

namespace cactus {
    using namespace Eigen;
    
    /**
    * error exception class for tiny-dnn
    **/
    class nn_error : public std::exception {
    public:
        explicit nn_error(const std::string &msg) : msg_(msg) {}
        const char *what() const throw() override { return msg_.c_str(); }

    private:
        std::string msg_;
    };

    inline std::string format_str(const char *fmt, ...) {
        static char buf[2048];

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt, args);
        va_end(args);
#ifdef _MSC_VER
#pragma warning(default : 4996)
#endif
        return std::string(buf);
    }
    template <typename T>
    struct index3d {
        index3d(T width, T height, T depth) { reshape(width, height, depth); }
        void reshape(T width, T height, T depth) {
            width_ = width;
            height_ = height;
            depth_ = depth;

            if ((int64_t)width * height * depth > std::numeric_limits<T>::max())
                throw nn_error(format_str(
                    "error while constructing layer: layer size too large for "
                    "tiny-dnn\nWidthxHeightxChannels=%dx%dx%d >= max size of "
                    "[%s](=%d)",
                    width, height, depth, typeid(T).name(), std::numeric_limits<T>::max()));
        }
        T width_;
        T height_;
        T depth_;
    };
    typedef index3d<size_t> shape3d;
    class bk_eigen {
    private:
        template<typename shape_type>
        shape3d toS3d(shape_type x) {
            switch (x.size()) {
            case 0:
                return shape3d(0, 0, 0);
            case 1:
                return shape3d(x[0], 1, 1);
            case 2:
                return shape3d(x[1], x[0], 1);
            case 3:
                return shape3d(x[2], x[1], x[0]);
            default:
                return shape3d(x[x.size() - 3], x[x.size() - 2], x[x.size() - 1]);
            }
        }
    public:
        template<typename Type>
        void bias_init(Type& dst, Type& src) {
            shape3d x3d = toS3d(dst.shape());
            shape3d y3d = toS3d(src.shape());
            Map<Matrix<Type::value_type, Dynamic, Dynamic, RowMajor>>
                d(dst.data(), x3d.height_, x3d.width_),
                s(src.data(), y3d.height_, y3d.width_);
            d.rightCols(y3d.width_) = s;
        }
        template<typename Type>
        void weights_init(Type& dst, Type& src) {
            shape3d x3d = toS3d(dst.shape());
            shape3d y3d = toS3d(src.shape());
            Map<Matrix<Type::value_type, Dynamic, Dynamic, RowMajor>>
                d(dst.data(), x3d.height_, x3d.width_),
                s(src.data(), y3d.height_, y3d.width_);
            d.leftCols(y3d.width_)= s;
        }
        template<typename Type>
        void full_connect(Type& x, Type& y, Type& z){
            shape3d x3d = toS3d(x.shape());
            shape3d y3d = toS3d(y.shape());
            shape3d z3d = toS3d(z.shape());
            Map<Matrix<Type::value_type, Dynamic, Dynamic, RowMajor>>
                a(x.data(), x3d.height_, x3d.width_),
                b(y.data(), y3d.height_, y3d.width_),
                r(z.data(), z3d.height_, z3d.width_);
            Matrix<Type::value_type, Dynamic, Dynamic, RowMajor>
                tmp(x3d.height_, x3d.width_+1);
            tmp.rightCols(x3d.width_).setOnes();
            tmp.leftCols(x3d.width_) = a;
            r = tmp*b.transpose();
        }

    };
}
#endif