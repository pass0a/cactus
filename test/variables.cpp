/*
  Copyright(C) 2018 liuwenjun.All rights reserved.
*/
#include <gtest/gtest.h>
#include <string.h>

#include <iostream>
#include <memory>

#include "framework/graph.hpp"
#include "framework/node.hpp"
#include "framework/operation.hpp"
#include "framework/placeholders.hpp"
#include "framework/session.hpp"
#include "framework/tensor.hpp"
#include "framework/variables.hpp"
#include "kernels/math.h"
#include "kernels/ops.hpp"

TEST(core, buffer) {
    cactus::Buffer x;
    x.resize(10);
    strcpy(reinterpret_cast<char *>(x.data()), "12345");
    EXPECT_STREQ("12345", (char *)x.data());
}
TEST(core, tensor) {
     cactus::Tensor x(cactus::kFloat, { 3, 2 });
     EXPECT_EQ(6*sizeof(float_t), x.TotalBytes());
     cactus::Tensor y(12.0215);
     EXPECT_EQ(*(double_t*)y.data(), 12.0215);
}
TEST(core, constant) {
    /*cactus::Graph g;
    auto x = cactus::Const(g, { { 1,3 },{ 2,4 } });
    auto y = cactus::Const(g, { { 1,3 },{ 2,4 } });
    auto a = cactus::Const(g, 2);
    auto z = cactus::Add(g,x,y);
    g.run(z);
    EXPECT_EQ(x.node()->tensor().shape().rows, 2);
    EXPECT_EQ(x.node()->tensor().shape().cols, 2);
    EXPECT_EQ(x.node()->tensor().TotalBytes(), 16);
    EXPECT_EQ(z.node()->tensor().get<int>(0),2);*/
////    EXPECT_EQ(iw[0], 1);
////    EXPECT_EQ(iw[1], 2);
////    EXPECT_EQ(iw[2], 3);
////    EXPECT_EQ(iw[3], 3);
////    EXPECT_EQ(iw[4], 5);
////    EXPECT_EQ(iw[5], 9);
////
////    x = cactus::Const({ { 1.0, 2.0, 12.9485 } });
////    EXPECT_EQ(x.shape().rows, 1);
////    EXPECT_EQ(x.shape().cols, 3);
////    EXPECT_EQ(x.TotalBytes(), 24);
////    double_t dw[3];
////    memcpy(dw, x.data(), x.TotalBytes());
////    EXPECT_EQ(dw[0], 1.0);
////    EXPECT_EQ(dw[1], 2.0);
////    EXPECT_EQ(dw[2], 12.9485);
}
TEST(core,matmul) {
    cactus::Graph g;
    auto x = cactus::Const(g, { { 1, 2 },{ 3, 5 } });
    auto y = cactus::Const(g, { { 1, 2 },{ 3, 5 } });
    auto z = cactus::matmul(g, x, y);
    g.run(z);
    EXPECT_EQ(x.node()->tensor().TotalBytes(), 16);
    int iw[4];
    memcpy(iw, z.node()->tensor().data(), z.node()->tensor().TotalBytes());
    EXPECT_EQ(iw[0], 7);
    EXPECT_EQ(iw[1], 12);
    EXPECT_EQ(iw[2], 18);
    EXPECT_EQ(iw[3], 31);
    //z = cactus::scalar_mul(2,x);
}
//TEST(core, placeholder) {
//    /*cactus::scope g;
//      auto z = cactus::add(g,1,2);
//      g.run(z);*/
//}
TEST(core, input) {
    /*cactus::Graph g;
    auto s=cactus::Const(g, { 10, 2, 3 });
    cactus::Input x(s);
    cactus::Tensor t = x.node()->tensor();
    EXPECT_EQ(t.get<int>(0), 10);
    EXPECT_EQ(t.get<int>(1), 2);
    EXPECT_EQ(t.get<int>(2), 3);*/
}
TEST(graph, scalarConst) {
    cactus::Graph g;
    auto x = cactus::Const(g.opName("x"), 1);
    auto y = cactus::Const(g.opName("y"), 2);
    auto a = cactus::Const(g.opName("a"), 3);
    auto z = cactus::Add(g.opName("z"), x, y);
    auto z1 = cactus::Add(g.opName("z1"), z, y);
    g.run(z1);
    EXPECT_EQ(5, z1.node()->tensor().get<int>(0));
    EXPECT_EQ(3, z.node()->tensor().get<int>(0));
    EXPECT_EQ(1, x.node()->tensor().get<int>(0));
}
TEST(graph, multiConst) {
    cactus::Graph g;
    auto x = cactus::Const(g.opName("x"), { { 1,2 },{3,4} });
    auto y = cactus::Const(g.opName("y"), { { 1,2 },{ 3,4 } }); 
    auto a = cactus::Const(g.opName("a"), 3);
    auto z = cactus::Add(g.opName("z"), x, y);
    auto z1 = cactus::Add(g.opName("z1"), z, y);
    g.run(z1);
    int iw[4];
    memcpy(iw, z1.node()->tensor().data(), z1.node()->tensor().TotalBytes());
    EXPECT_EQ(3, iw[0]);
    EXPECT_EQ(6, iw[1]);
    EXPECT_EQ(9, iw[2]);
    EXPECT_EQ(12, iw[3]);
}