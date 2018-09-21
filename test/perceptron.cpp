#include <gtest/gtest.h>
#include "framework/graph.hpp"
#include "framework/node.hpp"
#include "kernels/ops.hpp"
#include "kernels/eigenwrapper.h"
class active :public cactus::Operation {
public:
    active(cactus::Input x) {
        inputs = { x.node() };
    }
private:
    void compute() {
        auto x = inputs[0]->tensor();
        if (x.shape() == cactus::Shape({ 1,1 })) {
            if (x.get<int>(0)) {
                //auto xt = cactus::Map<int>::mapping(x);
                t = cactus::Tensor(cactus::DataTypeToEnum<int>::value, {1,1});
                t.set<int>(0,0);
                //xt(0, 0) = 1;
            }
        }
    }
};

TEST(exsample, perceptron) {
    //perceptron p(std::shared_ptr<cactus::operation>(new factive()));
    cactus::Graph g;
    auto result=g.insert(std::make_shared<active>( cactus::Const(g, { 1 })));
    g.run(result);
    EXPECT_EQ(0, result.node()->tensor().get<int>(0));
}
TEST(exsample, perceptron) {
    //perceptron p(std::shared_ptr<cactus::operation>(new factive()));
    cactus::Graph g;
    
    auto weight = cactus::Variable(g, { 1,1 }, cactus::DataType::kInt32);
    auto weight = cactus::Variable(g, { 1,1 }, cactus::DataType::kInt32);
    g.run(result);
    EXPECT_EQ(0, result.node()->tensor().get<int>(0));
}