#include "../cactus/util/eigen3/eigen3.hpp"
//#include "../cactus/util/bk_eigen.hpp"
//#include "../cactus/network.hpp"
//#include "../cactus/layers/input_layer.hpp"
//#include "../cactus/layers/fully_connected_layer.hpp"
#include <complex>

using namespace cactus;
void test_complex() {
    
    std::complex<float> x(1,1);
    Tensor<std::complex<float>> out;
    out = { x };
    auto z=out + 2.0f;
    std::cout<<z<<std::endl;
}
void test_assgin() {
    Tensor<float> z1({ 12 });
    z1 = { 1,2,3,4,5,6,7,8,9,10,11,12 };
    Tensor<float> z2;
    z2 = z1;
    z2.ref({ 0 }) = 15;
    std::cout<<z1.ref({ 0 }<<std::endl;
}
void test_sum() {
    Tensor<float> z1({ 12 });
    z1 = { 1,2,3,4,5,6,7,8,9,10,11,12 };
    auto len = z1.shape()[0];
    auto s = z1.subView({ {1,len - 1} }) - z1.subView({ { 0,len - 1 } })*0.97f;
    //z1.subView({ { 1,len - 1 } }) = s;
    auto s1 = pow(2, z1.subView({ { 1,len - 1 } }));
    auto s2 = sin(z1.subView({ { 1,len - 1 } }));
    std::cout << 1 - s1 << std::endl;
}
