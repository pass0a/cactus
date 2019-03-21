#include "../../../3rd/eigen/Eigen/Dense"
#include <gtest/gtest.h>
#include <vector>

#include <memory>

class Testst {
public:
    Testst(int v) {
        std::cout << v << std::endl;
    }
    Testst(std::initializer_list<int> sh) {
        val = sh;
        std::cout << *sh.begin() << std::endl;
    }
    std::vector<int> val;
};
TEST(layer, fully) {
    Testst t({3});
    /*using namespace Eigen;
    Eigen::Matrix<float, 4, 4, RowMajor> m;
    m << 1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16;
    Eigen::Matrix<float, 4,3, RowMajor> tmp;
    tmp << 1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12;
    auto t = tmp.block(0, 0, 3, 3).array() > m.block(0, 0, 3, 3).array();
    Eigen::Matrix<int, 3, 3, RowMajor> c;
    c= t.matrix();
    std::cout << m << std::endl;*/
}