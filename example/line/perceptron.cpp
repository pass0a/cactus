#include <iostream>
//#include "../../cactus/cactus.hpp"
//#include "../matplotlib/matplotlibcpp.h"
#include <Eigen\Dense>

int main() {
    using namespace Eigen;
    Array3i x;
    x << 1.0, 2.0, 3.0;
    auto tmp=log(x);
    std::cout << tmp << std::endl;
    return 0;
}