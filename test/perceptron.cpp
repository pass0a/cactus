#include <gtest/gtest.h>
#include "../src/tensor.hpp"
#include "../src/operation.hpp"

class perceptron {
public:
    perceptron(std::shared_ptr<cactus::operation> active) {
        active->input({1});
        active->compute();
    }
};
class factive :public cactus::operation {
public:
    void input(std::vector<cactus::Tensor> args) {
        x = args[0];
    }
    cactus::Tensor compute() {
        return cactus::Tensor(10.23);
        /*int x = x.scalar<int>();
        if (x > 0) {
            return cactus::Tensor(1);
        }
        return cactus::Tensor(0);*/
    }
    cactus::Tensor x;
};
TEST(exsample, perceptron) {
    perceptron p(std::shared_ptr<cactus::operation>(new factive()));

    EXPECT_EQ(1,1);
}