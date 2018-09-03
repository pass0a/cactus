#include <Eigen/Core>
#include <iostream>
#include "perceptron.hpp"

using namespace Eigen;
int f(double_t x) {
	std::cout << x << std::endl;
	return 0;
}
int main() {
	cactus::Perceptron<float, 10> m(f);
	Eigen::ArrayXd v1(10),v2(10);
	v1 << 1, 2, 3, 4, 5, 6, 7, 8, 9, 0;
	m.predict(v1);
	return 0;
}