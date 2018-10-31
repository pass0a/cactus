#include <Eigen/Dense>
#include "../framework/tensor.hpp"
namespace cactus {
template<class T>
struct Matrix
{
    typedef Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic,Eigen::RowMajor> type;
};
template<class T>
struct Map
{
    typedef Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> type;
    static type mapping(Tensor x) {
        return type((T*)x.data(), x.shape().rows, x.shape().cols);
    }
};

//template<typename T>
//Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic> wrap_log(Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic> val) {
//    return Eigen::log(val);
//}
#define TypeMatrix Eigen::ArrayWrapper<Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic,Eigen::RowMajor>>> 

template<typename T>
T wrap_log(T val) {
    return static_cast<T>(log(val));
}
template<typename T>
auto wrap_log(TypeMatrix val)
    ->decltype(Eigen::log(val)){
    return Eigen::log(val);
}

}
