#include <gtest/gtest.h>
#include "../cactus/xtensor/xtensor.hpp"
#include "../cactus/layers/input_layer.hpp"
#include <complex>

TEST(core, xstorage) {
    int buf[3 * 3] = {1,2,3,4,5,6,7,8,9};
    xt::uvector<int> m(buf,9);
    EXPECT_EQ(m.size(),9);
    std::vector<double> tmp = {1,2.4,15,3.,55,659};
    xt::uvector<double> n(tmp.data(),tmp.size());
    EXPECT_EQ(n.size(), 8);
}
TEST(core, xtensor1) {
    std::complex<double> m[2];
    //xt::xtensor<std::complex<double>> x;
    std::cout << m[0] <<"==>"<<m[1] << std::endl;
}
TEST(core, xtensor2) {
    int buf[3 * 3] = { 1,2,3,4,5,6,7,8};
    xt::xtensor<int> x(buf, {2,2,2});
    EXPECT_EQ(x.size(), 8);
    EXPECT_EQ(x.dim(), 3);
    EXPECT_EQ(x[0].dim(), 2);
    EXPECT_EQ(x.shape()[0], 2);
    EXPECT_EQ(x.shape()[1], 2);
    EXPECT_EQ(x.shape()[2], 2);
    /*EXPECT_EQ(x[0][0][1], 2);
    EXPECT_EQ(x[0][0][2], 2);*/
}
TEST(core, layers) {
    
}