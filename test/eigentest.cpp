#include "../3rd/eigen/Eigen/Dense"
#include <iostream>
int main() {
    Eigen::Array<float, 10, 1> tmp;
    tmp << 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9;
    Eigen::Array<float, 10, 1> z;
    z << 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9;
    // auto z = Eigen::ArrayXf::LinSpaced( 10, 0, 10 );
    // std::cout << z << std::endl;
    auto zy = z == tmp;
    std::cout << zy << std::endl;
    std::cout << 0.9 - 0.9 << std::endl;
    return 0;
}
