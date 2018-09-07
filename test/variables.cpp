/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <iostream>
#include <memory>

#include "../src/variables.hpp"
#include "../src/tensor.hpp"
#include "../src/placeholders.hpp"
#include "../src/oparetor.hpp"
#include "../src/session.hpp"
#include "../src/graph.hpp"
#include "../src/ops.hpp"


TEST(core, buffer) {
    /*cactus::graph g;
    cactus::session s;*/
    cactus::Buffer x;
    x.resize(10);
    strcpy((char*)x.data(),"12345");
    EXPECT_STREQ("1245", (char*)x.data());
}
TEST(core, tensor) {
    cactus::Tensor x(cactus::kFloat, { 3,2 });
    EXPECT_EQ(6*sizeof(float_t), x.TotalBytes());
}
TEST(core, constant) {
    //cactus::InputList list({ { 1,2,3 },{3,5,9} });
    //cactus::Const({ 1.1f,2.2f,3.3f });
    cactus::Const({ { 1,2,3 },{ 3,5,9 } });
    EXPECT_EQ(0,0);
}