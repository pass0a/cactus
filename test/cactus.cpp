#include <gtest/gtest.h>
#include "../cactus/core/framework/tensor.h"
#include "../cactus/util/bk_eigen.hpp"
#include "../cactus/util/eigen3.hpp"
#include "../cactus/network.hpp"
#include "../cactus/layers/input_layer.hpp"
#include "../cactus/layers/fully_connected_layer.hpp"
#include <complex>

using namespace cactus;

TEST(core, xtensor1) {
    tensor<int> x = { 1,2,3,4,5,6,7,8,9,10,11,12 };
    x.reshape({ 4,3 });
    auto y = x + 2;
    std::cout << y.ref({ 0,0 }) << std::endl;
}
TEST(core, xtensor) {
    tensor<int> x = { 1,2,3,4,5,6,7,8,9,10,11,12};
    x.reshape({2,2,3});
    int* p = x[1].data();
    EXPECT_EQ(x.size(), 12);
    EXPECT_EQ(x.dim(), 3);
    EXPECT_EQ(x[0][0].size(), 3);
    EXPECT_EQ(x.shape()[0], 2);
    EXPECT_EQ(x.shape()[1], 2);
    EXPECT_EQ(x.shape()[2], 3);
    EXPECT_EQ(x.ref({1,1,2}), 12);
}
TEST(core, xview) {
    xt::xarray<int>::container_type buf = {1,2,3,4,4,6,7,8,9};
    xt::xarray<int> x(buf,{2,2,2});
    
    xt::xview<xt::xarray<int>> y(x, 0, {2,2});
    int i = 1;
    for (auto iter = y.begin(); iter != y.end(); iter++) {
        EXPECT_EQ(*iter,i++);
    }
}
TEST(core, complex) {
    /*std::vector<std::complex<int>> m;
    m[0] = std::complex<int>(1, 1);
    m[0] = std::complex<int>(1, 1);
    cactus::Tensor<std::complex<int>> out(m, { 2,2 });
    EXPECT_EQ(out.size(), 2);
    EXPECT_EQ(m.size(), 0);*/
}
TEST(layer, input) {
    tensor<int> in_data={1,2,3,4} , out_data({ 4 });
    input_layer<bk_eigen,int> il({2});
    il.forward(in_data,out_data);
    EXPECT_EQ(out_data.ref({ 0 }), 1);
    EXPECT_EQ(out_data.ref({ 1 }), 2);
    EXPECT_EQ(out_data.ref({ 2 }), 3);
    EXPECT_EQ(out_data.ref({ 3 }), 4);
}
TEST(layer, fully) {
    fully_connected_layer<bk_eigen> l(4, 2);
    tensor<> w = { 1,1,1,1,2,2,2,2 }, b = {1,1};
    tensor<> out;
    out.reshape({ 2 });
    w.reshape({ 2, 4 });
    b.reshape({ 2, 1 });
    l.weight_init(w);
    l.bias_init(b);
    l.forward({ 0, 1, 2, 3 }, out);

    for (size_t i = 0; i < out.size(); i++) {
        EXPECT_FLOAT_EQ(out.data()[i], i*6+6+1);
    }
}