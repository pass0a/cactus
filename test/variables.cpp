/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/
#include <string.h>
#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "framework/variables.hpp"
#include "framework/tensor.hpp"
#include "framework/placeholders.hpp"
#include "framework/operation.hpp"
#include "framework/session.hpp"
#include "framework/graph.hpp"
#include "framework/node.hpp"
#include "kernels/ops.hpp"
#include "kernels/math.h"

TEST(core, buffer) {
    cactus::Buffer x;
    x.resize(10);
    strcpy_s(reinterpret_cast<char*>(x.data()), 10, "12345");
    EXPECT_STREQ("12345", (char*)x.data());
}
TEST(core, tensor) {
    cactus::Tensor x(cactus::kFloat, { 3, 2 });
    EXPECT_EQ(6*sizeof(float_t), x.TotalBytes());
    cactus::Tensor y(12.0215);
    EXPECT_EQ(*(double_t*)y.data(), 12.0215);
}
//TEST(core, constant) {
//    cactus::Tensor x = cactus::Const({ { 1, 2, 3 }, { 3, 5, 9 } });
//    int iw[6];
//    memcpy(iw, x.data(), x.TotalBytes());
//    EXPECT_EQ(x.shape().rows, 2);
//    EXPECT_EQ(x.shape().cols, 3);
//    EXPECT_EQ(x.TotalBytes(), 24);
//    EXPECT_EQ(iw[0], 1);
//    EXPECT_EQ(iw[1], 2);
//    EXPECT_EQ(iw[2], 3);
//    EXPECT_EQ(iw[3], 3);
//    EXPECT_EQ(iw[4], 5);
//    EXPECT_EQ(iw[5], 9);
//
//    x = cactus::Const({ { 1.0, 2.0, 12.9485 } });
//    EXPECT_EQ(x.shape().rows, 1);
//    EXPECT_EQ(x.shape().cols, 3);
//    EXPECT_EQ(x.TotalBytes(), 24);
//    double_t dw[3];
//    memcpy(dw, x.data(), x.TotalBytes());
//    EXPECT_EQ(dw[0], 1.0);
//    EXPECT_EQ(dw[1], 2.0);
//    EXPECT_EQ(dw[2], 12.9485);
//}
//TEST(core,matmul) {
//    cactus::Tensor x = cactus::Const({ { 1, 2},{ 3, 5} });
//    cactus::Tensor y = cactus::Const({ { 1, 2 },{ 3, 5 } });
//    cactus::Tensor z = cactus::matmul(x, y);
//    EXPECT_EQ(x.TotalBytes(), 16);
//    int iw[4];
//    memcpy(iw, z.data(), x.TotalBytes());
//    EXPECT_EQ(iw[0], 7);
//    EXPECT_EQ(iw[1], 12);
//    EXPECT_EQ(iw[2], 18);
//    EXPECT_EQ(iw[3], 31);
//    //z = cactus::scalar_mul(2,x);
//}
TEST(core, placeholder) {
    /*cactus::scope g;
    auto z = cactus::add(g,1,2);
    g.run(z);*/
}
TEST(core, node) {
    //std::shared_ptr<cactus::Node> z = std::shared_ptr<cactus::Node>(new cactus::Tensor());
    
}
TEST(core, input) {
    cactus::Input x({ 10,2,3 });
    cactus::Tensor t=x.tensor();
    std::cout << *(int*)t.data() << std::endl;
}
TEST(core, operation) {
    cactus::Operation x;
    //x.put(3);
}
TEST(core, graph) {
    /*cactus::graph g;
    cactus::Tensor p = cactus::Placeholder(g.named("p"), 
        cactus::DataType::kInt32,
        {2,2});
    cactus::Tensor x = cactus::Const(g,{ { 1, 2 },{ 3, 5 } });
    cactus::Tensor y = cactus::Const(g,{ { 1, 2 },{ 3, 5 } });
    cactus::Tensor z = cactus::matmul(g,x, y);
    cactus::matmul(g,z, x);
    g.run({"z"});
    EXPECT_EQ(x.TotalBytes(), 16);
    int iw[4];
    memcpy(iw, z.data(), x.TotalBytes());
    EXPECT_EQ(iw[0], 7);
    EXPECT_EQ(iw[1], 12);
    EXPECT_EQ(iw[2], 18);
    EXPECT_EQ(iw[3], 31);*/
    //z = cactus::scalar_mul(2,x);
}