#include <gtest/gtest.h>
#include "../cactus/core/framework/tensor.h"
#include "../cactus/util/bk_eigen.hpp"
#include "../cactus/network.hpp"
#include "../cactus/layers/input_layer.hpp"
#include "../cactus/layers/fully_connected_layer.hpp"
#include <complex>

using namespace cactus;

TEST(core, xtensor) {
    tensor<int>::container_type buf = { 1,2,3,4,5,6,7,8,9,10,11,12};
    tensor<int> x(buf,{2,2,3});
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
    bk_eigen bk;
    tensor<int> in_data({1,2,3,4},{ 4 }), out_data({ 4 });
    input_layer<int> il({2});
    il.forward(in_data,out_data,bk);
    EXPECT_EQ(in_data.ref({ 0 }), 1);
    EXPECT_EQ(in_data.ref({ 1 }), 2);
    EXPECT_EQ(in_data.ref({ 2 }), 3);
    EXPECT_EQ(in_data.ref({ 3 }), 4);
}
TEST(layer, fully) {
    bk_eigen bk;
    fully_connected_layer<> l({ 4 }, { 2 });
    
    l.weight_init(tensor<>({ 1,1,1,1 }, {2,2}));
    /*l.bias_init(weight_init::constant(0.5));*/

    tensor<> in({ 0, 1, 2, 3 }, {2,2});
    tensor<> out;
    l.forward(in, out,bk);

    for (size_t i = 0; i < out.size(); i++) {
        std::cout << out.data()[i] << std::endl;
        /*EXPECT_FLOAT_EQ(out_expected[i], out[i]);*/
    }
}