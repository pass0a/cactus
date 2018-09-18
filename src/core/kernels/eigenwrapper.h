#include <Eigen/Dense>

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
};
}
