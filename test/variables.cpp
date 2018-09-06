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


TEST(core, variables) {
    /*cactus::graph g;
    cactus::session s;*/
    cactus::Buffer x;
    x.resize(10);
    strcpy((char*)x.data(),"12345");
    EXPECT_STREQ("1245", (char*)x.data());
}
