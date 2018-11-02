/*
  Copyright(C) 2018 liuwenjun.All rights reserved.
*/
#include <gtest/gtest.h>
#include <string.h>

#include <iostream>
#include <memory>

#include "cactus.hpp"

#include <vector>

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
    EXPECT_EQ(x.tensor().totalBytes(), 16);
    int iw[4];
    memcpy(iw, z.tensor().data(), z.tensor().totalBytes());
    EXPECT_EQ(iw[0], 7);
    EXPECT_EQ(iw[1], 12);
    EXPECT_EQ(iw[2], 18);
    EXPECT_EQ(iw[3], 31);
    // z = cactus::scalar_mul(2,x);
}
TEST(math, pow) {
    cactus::Graph g;
    auto x = cactus::Const(g, { { 1, 2 },{ 3, 4 } });
    auto y = cactus::Const(g, { { 1, 2 },{ 3, 4 } });
    auto z = cactus::pow(g, x, y);
    g.run(z);
    EXPECT_EQ(x.tensor().totalBytes(), 16);
    int iw[4];
    memcpy(iw, z.tensor().data(), z.tensor().totalBytes());
    EXPECT_EQ(iw[0], 1);
    EXPECT_EQ(iw[1], 4);
    EXPECT_EQ(iw[2], 27);
    EXPECT_EQ(iw[3], 256);
    // z = cactus::scalar_mul(2,x);
}
TEST(math, pow1) {
    cactus::Graph g;
    auto x = cactus::Const(g, 3);
    auto y = cactus::Const(g, 5);
    auto z = cactus::pow(g, x, y);
    g.run(z);
    EXPECT_EQ(x.tensor().totalBytes(), 4);
    EXPECT_EQ(z.tensor().get<int>(0), 243);
    // z = cactus::scalar_mul(2,x);
}
TEST(math, pow2) {
    cactus::Graph g;
    auto x = cactus::Variable(g.opName("x"), { { 1, 2 },{ 3, 4 } });
    auto y = cactus::Const(g, 3);
    auto z = cactus::pow(g, x, y);
    g.run(g.initAllVariable());
    g.run(z);
    EXPECT_EQ(x.tensor().totalBytes(), 16);
    EXPECT_EQ(z.tensor().get<int>(0), 1);
    EXPECT_EQ(z.tensor().get<int>(1), 8);
    EXPECT_EQ(z.tensor().get<int>(2), 27);
    EXPECT_EQ(z.tensor().get<int>(3), 64);
    // z = cactus::scalar_mul(2,x);
}
TEST(core, placeholder) {
    cactus::Graph g;
    auto a = cactus::Placeholder(g.opName("x"), cactus::DataType::kDouble, { 2,2 });
    auto b = cactus::Const(g, { {1,2,},{3,4,} });
    auto z = cactus::add(g,a,b);
    g.run(z, { { "x",{{1,2,},{3,3,}} }, {"y",a} });
    EXPECT_EQ(z.tensor().get<int>(0), 2);
    EXPECT_EQ(z.tensor().get<int>(1), 4);
    EXPECT_EQ(z.tensor().get<int>(2), 6);
    EXPECT_EQ(z.tensor().get<int>(3), 7);
}
TEST(core, add) {
    cactus::Graph g;
    
    auto x = cactus::Variable(g, {10, 2, 3});
    auto y = cactus::Variable(g, {12, 5, 3});
    auto new_x = cactus::add(g, x, y);
    auto z=cactus::assign(g,x,new_x);
    auto new_y = cactus::add(g, z, y);
    z = cactus::assign(g,x,new_y);

    auto init = g.initAllVariable();
    g.run(init);
    g.run(z);
    EXPECT_EQ(x.tensor().data(), z.tensor().data());
    EXPECT_EQ(z.tensor().get<int>(0), 34);
    EXPECT_EQ(x.tensor().get<int>(0), 34);
    EXPECT_EQ(z.tensor().get<int>(1), 12);
    EXPECT_EQ(z.tensor().get<int>(2), 9);
    g.run(z);
    EXPECT_EQ(x.tensor().data(), z.tensor().data());
    EXPECT_EQ(z.tensor().get<int>(0), 58);
    EXPECT_EQ(x.tensor().get<int>(0), 58);
    EXPECT_EQ(x.tensor().get<int>(1), 22);
    EXPECT_EQ(x.tensor().get<int>(2), 15);
    EXPECT_EQ(y.tensor().get<int>(0), 12);
    EXPECT_EQ(y.tensor().get<int>(1), 5);
    EXPECT_EQ(y.tensor().get<int>(2), 3);
}
TEST(core, variable) {
    cactus::Graph g;
    auto x = cactus::Variable(g, {10, 2, 3});
    auto y = cactus::Variable(g, {12, 5, 3});
    // auto z=cactus::Add(g,x,y);
    auto init = g.initAllVariable();
    g.run(init);
    EXPECT_EQ(x.tensor().get<int>(0), 10);
    EXPECT_EQ(x.tensor().get<int>(1), 2);
    EXPECT_EQ(x.tensor().get<int>(2), 3);
    EXPECT_EQ(y.tensor().get<int>(0), 12);
    EXPECT_EQ(y.tensor().get<int>(1), 5);
    EXPECT_EQ(y.tensor().get<int>(2), 3);
}
TEST(matrix, variable) {
    cactus::Graph g;
    auto x = cactus::Variable(g, { {1,2} , {3,4} });
    auto y = cactus::Variable(g, { {12, 5},{ 3,9} });
    // auto z=cactus::Add(g,x,y);
    auto init = g.initAllVariable();
    g.run(init);
    EXPECT_EQ(x.tensor().get<int>(0), 1);
    EXPECT_EQ(x.tensor().get<int>(1), 2);
    EXPECT_EQ(x.tensor().get<int>(2), 3);
    EXPECT_EQ(x.tensor().get<int>(3), 4);
}
TEST(graph, scalarConst) {
    cactus::Graph g;
    auto x = cactus::Const(g.opName("x"), 1);
    auto y = cactus::Const(g.opName("y"), 2);
    auto a = cactus::Const(g.opName("a"), 3);
    auto z = cactus::add(g.opName("z"), x, y);
    auto z1 = cactus::add(g.opName("z1"), z, y);
    g.run(z1);
    EXPECT_EQ(5, z1.tensor().get<int>(0));
    EXPECT_EQ(3, z.tensor().get<int>(0));
    EXPECT_EQ(1, x.tensor().get<int>(0));
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
    memcpy(iw, z1.tensor().data(), z1.tensor().totalBytes());
    EXPECT_EQ(3, iw[0]);
    EXPECT_EQ(6, iw[1]);
    EXPECT_EQ(9, iw[2]);
    EXPECT_EQ(12, iw[3]);
}
TEST(core,qiudao) {
    cactus::Graph g;
    auto x = cactus::Variable(g.opName("x"), { { 1.0, 2.0 },{ 3.0, 4.0 } });
    auto a = cactus::Const(g.opName("a"), 3.0);
    auto y = cactus::pow(g.opName("y"), x,a);
    auto dy = cactus::backward(g,y);
    auto dydx = cactus::grad(g,dy,a);
    auto init = g.initAllVariable();
    g.run(init);
    g.run(dydx);
 /*   EXPECT_EQ(3, dydx.tensor().get<double>(0));
    EXPECT_EQ(12, dydx.tensor().get<double>(1));
    EXPECT_EQ(27, dydx.tensor().get<double>(2));
    EXPECT_EQ(48, dydx.tensor().get<double>(3));*/
    /*EXPECT_EQ(12, z.tensor().get<int>(1));
    EXPECT_EQ(27, z.tensor().get<int>(2));
    EXPECT_EQ(48, z.tensor().get<int>(3));*/
}
TEST(math, sum) {
    cactus::Graph g;
    auto x = cactus::Const(g.opName("x"), { { 1, 2 },{ 3, 4 } });
    auto y = cactus::Const(g.opName("y"), { { 1, 2 },{ 3, 4 } });
    auto z = cactus::add(g.opName("z"), x,y);
    auto z1 = cactus::sum(g.opName("z1"), z);
    g.run(z1);
    EXPECT_EQ(20, z1.tensor().get<int>(0));
}
