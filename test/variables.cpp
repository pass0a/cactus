#include "../../../3rd/eigen/Eigen/Dense"
#include <gtest/gtest.h>
#include <vector>


TEST(layer, fully) {
    using namespace Eigen;
    Array3cf x;
    Array3f x1;
    x1 << 1.0, 3.0, 4.0;
    x << (1.0f, 20.0f), (3.0f, 20.0f), (1.0f, 10.0f) ;
    std::complex<float> y(1.0f, 2.0f),z(1.0f,5);
    Eigen::pow(x1, 3.0f);
    Eigen::pow(x1, 3);
    auto r1=Eigen::pow(x1,2);
    auto r2=Eigen::pow(x1, y);
    std::cout << r1<< std::endl;
}