#include <gtest/gtest.h>
#include "framework/graph.hpp"
#include "framework/node.hpp"
#include "kernels/ops.hpp"
#include "kernels/eigenwrapper.h"
namespace cactus {
    typedef int(*sigmal)(double_t);

    template<typename T, uint16_t num>
    class Perceptron {
    public:
        Perceptron(sigmal activator) :weights(num) {
            this->activator = activator;
            weights.setOnes();
            bias = 0;
        }
        int predict(Eigen::ArrayXd input_vec) {
            assert(input_vec.size() == num);
            return activator((weights*input_vec).sum() + bias);
        }
        friend std::ostream& operator <<(std::ostream& os, Perceptron& p) {
            os << p.weights;
            return os;
        }
    private:
        int updateWeights(Eigen::ArrayXd input_vec, double_t output, double_t label, double_t rate) {
            double_t delta = label - output;

        }

    private:
        sigmal activator;
        Eigen::ArrayXd weights;
        double_t bias;
    };
}

TEST(exsample, perceptron) {
    //perceptron p(std::shared_ptr<cactus::operation>(new factive()));
    cactus::Graph g;
    auto result=g.insert(std::make_shared<active>( cactus::Const(g, { 1 })));
    g.run(result);
    EXPECT_EQ(0, result.node()->tensor().get<int>(0));
}
TEST(exsample, perceptron1) {
    //perceptron p(std::shared_ptr<cactus::operation>(new factive()));
    cactus::Graph g;
    
    // auto weight = cactus::Variable(g, { 1,1 }, cactus::DataType::kInt32);
    // auto weight1 = cactus::Variable(g, { 1,1 }, cactus::DataType::kInt32);
    // g.run(result);
    // EXPECT_EQ(0, result.node()->tensor().get<int>(0));
    
}
