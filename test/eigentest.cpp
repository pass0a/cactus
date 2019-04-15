#include "../3rd/eigen/Eigen/Dense"
#include <iostream>
int main() {
    Eigen::Array3i sample;
    sample << 1, 2, 3;
    std::cout << sample.cast<double>() * 0.1 << std::endl;
    return 0;
}
