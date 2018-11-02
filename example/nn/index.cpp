#include <iostream>
#include "cactus.hpp"

int main() {
    cactus::Graph g;
    int iv[][2] = { {1,1},{ 0,0 },{ 1,0 },{ 0,1 } };
    int labels[] = { 1,0,0,0 };
    auto weights = cactus::Variable(g, { 1,1 });
    auto bias = cactus::Variable(g, 0);
    auto input_vec = cactus::Placeholder(g.opName("input"), cactus::kInt32, {1,2});
    auto activator = cactus::add(g,
        cactus::dot(g, weights, input_vec)
        ,bias);
    auto label = cactus::Placeholder(g.opName("label"),cactus::kInt32);
    auto rate = cactus::Const(g, 0.1);
    auto delta = cactus::Variable(g, 0);
    auto delta_assgin =cactus::assign(g, delta, cactus::sub(g,activator,label));
    auto weights_assgin=cactus::add(g,weights,cactus::product(g,input_vec,cactus::product(g,delta_assgin,rate)));
    auto bias_assgin = cactus::add(g,rate,delta);
    g.run(g.initAllVariable());
    for (int i = 0; i < 10;i++) {
        for (int j = 0; j < 4;j++) {
            g.run(weights_assgin, { { "input",{iv[j][0],iv[j][1]} },{ "label",labels[j] } });
            rate.dump();
            delta.dump();
            g.run(bias_assgin, { { "input",{ iv[j][0],iv[j][1] } },{ "label",labels[j] } });
            rate.dump();
            delta.dump();
        }
    }
    
    return 0;
}