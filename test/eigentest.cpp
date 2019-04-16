#include "../3rd/eigen/Eigen/Dense"
#include <iostream>
int main() {
    auto z = Eigen::ArrayXf::LinSpaced( 10, 0, 2 );
    std::cout << z << std::endl;
    auto zz = z > 1;
    std::cout << zz << std::endl;
    auto zy = z > zz;
    std::cout << zy << std::endl;
    return 0;
}
