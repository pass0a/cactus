#include <Eigen/Dense>
#include <framework/tensor.hpp>
namespace cactus {
template<class T>
struct Matrix
{
    typedef Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> type;
};
template<class T>
struct Map
{
    typedef Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> type;
    static type mapping(Tensor x) {
        return type((T*)x.data(), x.shape().rows, x.shape().cols);
    }
};
//template<typename T>
//Map<T>::type mapTensor(Tensor x) {
//    return Map<T>::type((T*)x.data(), x.shape().rows, x.shape().cols);
//}
}
