#include <gtest/gtest.h>
#include "../cactus/core/framework/tensor.h"
#include "../cactus/layers/input_layer.hpp"
#include <complex>

using namespace cactus;

TEST(core, xtensor) {
    Tensor<int>::container_type buf = { 1,2,3,4,5,6,7,8,9,10,11,12};
    Tensor<int> x(buf,{2,2,3});
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
    xt::xarray<int>::container_type buf = {1,2,3,4,5,6,7,8,9};
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
    int vals[2] = {0,0};
    input_layer<int> in({2});
    in.inputs(vals,2);
    in.outputs();
}