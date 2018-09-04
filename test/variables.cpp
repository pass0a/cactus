#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../src/variables.hpp"
#include <iostream>
using namespace Eigen;
TEST(core,variables) {
	MatrixXd A(2,2),Y(2,2);
	MatrixXi b(1,2);
	ArrayXi v(2);
	A << 1, 2, 3, 4;
	v << 1, 2;
	std::cout << A.determinant() << std::endl;
	EXPECT_EQ(1, 10);
}