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
    cactus::Tensor x(cactus::kFloat, {3, 2});
    EXPECT_EQ(6 * sizeof(float_t), x.totalBytes());
    cactus::Tensor y(12.0215);
    EXPECT_EQ(*(double_t *)y.data(), 12.0215);
}
TEST(core, matmul) {
    cactus::Graph g;
    auto x = cactus::Const(g, {{1, 2}, {3, 5}});
    auto y = cactus::Const(g, {{1, 2}, {3, 5}});
    auto z = cactus::matmul(g, x, y);
    g.run(z);
    EXPECT_EQ(x.node()->tensor().totalBytes(), 16);
    int iw[4];
    memcpy(iw, z.node()->tensor().data(), z.node()->tensor().totalBytes());
    EXPECT_EQ(iw[0], 7);
    EXPECT_EQ(iw[1], 12);
    EXPECT_EQ(iw[2], 18);
    EXPECT_EQ(iw[3], 31);
    // z = cactus::scalar_mul(2,x);
}
// TEST(core, placeholder) {
//    /*cactus::scope g;
//      auto z = cactus::add(g,1,2);
//      g.run(z);*/
//}
TEST(core, variable1) {
    cactus::Graph g;
    auto x = cactus::Variable(g, {10, 2, 3});
    auto y = cactus::Variable(g, {12, 5, 3});
    auto new_x = cactus::add(g, x, y);
    auto z=cactus::assign(g,x,new_x);
    auto init = g.initAllVariable();
    g.run(init);
    g.run(z);
    EXPECT_EQ(z.node()->tensor().get<int>(0), 22);
    EXPECT_EQ(z.node()->tensor().get<int>(1), 7);
    EXPECT_EQ(z.node()->tensor().get<int>(2), 6);
    g.run(z);
    EXPECT_EQ(x.node()->tensor().get<int>(0), 34);
    EXPECT_EQ(x.node()->tensor().get<int>(1), 12);
    EXPECT_EQ(x.node()->tensor().get<int>(2), 9);
}
TEST(core, variable) {
    cactus::Graph g;
    auto x = cactus::Variable(g, {10, 2, 3});
    auto y = cactus::Variable(g, {12, 5, 3});
    // auto z=cactus::Add(g,x,y);
    auto init = g.initAllVariable();
    g.run(init);
    EXPECT_EQ(x.node()->tensor().get<int>(0), 10);
    EXPECT_EQ(x.node()->tensor().get<int>(1), 2);
    EXPECT_EQ(x.node()->tensor().get<int>(2), 3);
    EXPECT_EQ(y.node()->tensor().get<int>(0), 12);
    EXPECT_EQ(y.node()->tensor().get<int>(1), 5);
    EXPECT_EQ(y.node()->tensor().get<int>(2), 3);
}
TEST(graph, scalarConst) {
    cactus::Graph g;
    auto x = cactus::Const(g.opName("x"), 1);
    auto y = cactus::Const(g.opName("y"), 2);
    auto a = cactus::Const(g.opName("a"), 3);
    auto z = cactus::add(g.opName("z"), x, y);
    auto z1 = cactus::add(g.opName("z1"), z, y);
    g.run(z1);
    EXPECT_EQ(5, z1.node()->tensor().get<int>(0));
    EXPECT_EQ(3, z.node()->tensor().get<int>(0));
    EXPECT_EQ(1, x.node()->tensor().get<int>(0));
}
TEST(graph, multiConst) {
    cactus::Graph g;
    auto x = cactus::Const(g.opName("x"), {{1, 2}, {3, 4}});
    auto y = cactus::Const(g.opName("y"), {{1, 2}, {3, 4}});
    auto a = cactus::Const(g.opName("a"), 3);
    auto z = cactus::add(g.opName("z"), x, y);
    auto z1 = cactus::add(g.opName("z1"), z, y);
    g.run(z1);
    int iw[4];
    memcpy(iw, z1.node()->tensor().data(), z1.node()->tensor().totalBytes());
    EXPECT_EQ(3, iw[0]);
    EXPECT_EQ(6, iw[1]);
    EXPECT_EQ(9, iw[2]);
    EXPECT_EQ(12, iw[3]);
}
