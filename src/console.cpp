#include <iostream>
#include "Eigen/Dense"
int main() {
    Eigen::Matrix<int, 2, 1> m;
    Eigen::Matrix<int, 1, 2> n;
    Eigen::Vector2i z;
    m << 1, 2;
    n << 1, 2;
    std::cout << "" << m.rows() <<m.cols() << std::endl;
    std::cout << "" << n.rows() << n.cols() << std::endl;
    return 0;
}