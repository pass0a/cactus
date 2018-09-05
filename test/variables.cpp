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


class active :public cactus::oparetor {
public:
    void put() {
        
    }
    void compute() {
        std::cout << ctx.size() << std::endl;
    }
private:
    std::vector<std::shared_ptr<cactus::tensor>> ctx;
};
template<typename T>
class var :public cactus::tensor
, public std::enable_shared_from_this<var<T>> {
    
};
TEST(core, variables) {
    session s;
    active a;
    active b;
    a.put<int>((1));
    a.put<float>(3.0);
    b.put<active>(a);
    s.run(a);
    EXPECT_EQ(1, 10);
}
