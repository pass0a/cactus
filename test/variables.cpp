#include "../../../3rd/eigen/Eigen/Dense"
#include <gtest/gtest.h>
#include <vector>

#include <memory>

template<typename T>
using pod_type = typename std::enable_if<std::is_trivial<T>::value, T>::type;

template<typename T>
void test11(pod_type<T> arg1) {
    std::cout << arg1 << std::endl;
}
TEST(layer, fully) {
    //Testst t({3});
    test11<float>(0.5f);
   
}