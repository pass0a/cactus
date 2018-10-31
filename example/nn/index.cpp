#include <Eigen/Dense>
#include <iostream>

int main() {
    int data[] = { 1,2,3,4,5,6,7,8,9 };
    Eigen::Map<Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic,Eigen::RowMajor>> m(data,2,3);
    std::cout << m << std::endl;
}