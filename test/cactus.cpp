#include <gtest/gtest.h>
#include "../cactus/util/eigen3/eigen3.hpp"
//#include "../cactus/util/bk_eigen.hpp"
//#include "../cactus/network.hpp"
//#include "../cactus/layers/input_layer.hpp"
//#include "../cactus/layers/fully_connected_layer.hpp"
#include <complex>

using namespace cactus; 

//TEST(core, GreatThan) {
//    tensor<> x = { 5.0,3.0,4.0 };
//    tensor<> x1 = { 5.0,3.0,4.0 };
//    std::complex<float> p(2.0f,1.0f);
//    tensor<std::complex<float>> tmp = {(1.0f,2.0f),(4.0f,2.0f) ,(1.0f,3.0f) };
//    tensor<> y = 2;
//    int y2 = 2;
//    auto z = cactus::pow(x, x1);
//    auto z1 = cactus::pow(x, y);
//    auto z2 = cactus::pow(y, x);
//    auto z3 = cactus::pow(y, 3);
//    auto z4 = cactus::pow(tmp,2.0f);
//    //std::cout << z << z1 << z2  << std::endl;
//    /*EXPECT_EQ(z.ref({ 0 }), 1);
//    EXPECT_EQ(z.ref({ 1 }), 0);
//    EXPECT_EQ(z.ref({ 2 }), 0);*/
//}
//TEST(core, autograd) {
//    tensor<float> x = { 5.0,3.0,4.0 };
//    tensor<float> y = { 3.0,1.0,1.0 };
//    auto z = sqrt(x);
//    z.backward();
//    z = x + y;
//    z.backward();
//    z = x - y;
//    z.backward();
//    z = x * x;
//    z.backward();
//    z = log(y);
//    z.backward();
//    z = abs(x);
//    z.backward();
//    z = log10(x);
//    z.backward();
//    z = exp(x);
//    z.backward();
//
//}
//TEST(core, xtensor) {
//    tensor<int> x = { 1,2,3,4,5,6,7,8,9,10,11,12};
//    x.reshape({2,2,3});
//    
//    int* p = x[1].data();
//    EXPECT_EQ(x.size(), 12);
//    EXPECT_EQ(x.dim(), 3);
//    EXPECT_EQ(x[0][0].size(), 3);
//    EXPECT_EQ(x.shape()[0], 2);
//    EXPECT_EQ(x.shape()[1], 2);
//    EXPECT_EQ(x.shape()[2], 3);
//    EXPECT_EQ(x.ref({1,1,2}), 12);
//}
TEST(core, subview) {
    Tensor<float> z1({ 3,4 });
    z1 = { 1,2,3,4,5,6,7,8,9,10,11,12 };
    z1.reshape({ 3, 4 });
    std::cout << z1 << std::endl;
    auto x = z1.subView({ {0,2},{0,2} });
    auto y = z1.subView({ { 1,2 },{ 2,2 } });
    std::cout << (y*x) << std::endl;
    std::cout << x*3 << std::endl;
    std::cout << 3*y << std::endl;
    std::cout << (y>x) << std::endl;
    std::cout << sin(x) << std::endl;
    std::cout << cos(x) << std::endl;
    //std::cout << z3 << std::endl;
}
//TEST(core, xview) {
//    xt::xarray<int>::container_type buf = {1,2,3,4,4,6,7,8,9};
//    xt::xarray<int> x(buf,{2,2,2});
//    
//    xt::xview<xt::xarray<int>> y(x, 0, {2,2});
//    int i = 1;
//    for (auto iter = y.begin(); iter != y.end(); iter++) {
//        EXPECT_EQ(*iter,i++);
//    }
//}
//TEST(core, complex) {
//    cactus::tensor<std::complex<float>> out({ (1.0f, 1.0f),(1.0f, 1.0f) });
//    cactus::tensor<> cc;
//    std::complex<int> x(1,1);
//    auto z=x + 2;
//    cactus::pow(cc, 2.0f);
//    EXPECT_EQ(out.size(), 2);
//    EXPECT_EQ(z.real(), 2);
//}
//TEST(layer, input) {
//    tensor<int> in_data={1,2,3,4} , out_data({ 4 });
//    input_layer<bk_eigen,int> il({2});
//    il.forward(in_data,out_data);
//    EXPECT_EQ(out_data.ref({ 0 }), 1);
//    EXPECT_EQ(out_data.ref({ 1 }), 2);
//    EXPECT_EQ(out_data.ref({ 2 }), 3);
//    EXPECT_EQ(out_data.ref({ 3 }), 4);
//}
//TEST(layer, fully) {
//    fully_connected_layer<bk_eigen> l(4, 2);
//    tensor<> w = { 1,1,1,1,2,2,2,2 }, b = {1,1};
//    tensor<> out;
//    out.reshape({ 2 });
//    w.reshape({ 2, 4 });
//    b.reshape({ 2, 1 });
//    l.weight_init(w);
//    l.bias_init(b);
//    l.forward({ 0, 1, 2, 3 }, out);
//
//    for (size_t i = 0; i < out.size(); i++) {
//        EXPECT_FLOAT_EQ(out.data()[i], i*6+6+1);
//    }
//}