#include <iostream>
#include "cactus.hpp"


int main() {
    cactus::Graph g;
    int iv[][2] = { {1,1},{ 0,0 },{ 1,0 },{ 0,1 } };
    int labels[] = { 1,0,0,0 };
    
    auto weights = cactus::Variable(g, { 0,0 });
    auto bias = cactus::Variable(g, 0);
    auto input_vec = cactus::Placeholder(g.opName("input"), cactus::kInt32, {1,2});
    auto label = cactus::Placeholder(g.opName("label"), cactus::kInt32);
    auto rate = cactus::Const(g, 0.1);

    auto predict = cactus::add(g,
        cactus::dot(g, weights, input_vec)
        ,bias);
    auto activator = cactus::cond(g, cactus::gt(g,predict,cactus::Const(g,0)), cactus::Const(g,1), cactus::Const(g,0));
    
    auto delta = cactus::Variable(g, 0);
    auto delta_assgin =cactus::assign(g, delta, cactus::sub(g, label, activator));
    auto weights_assgin=cactus::assign(g,weights,cactus::add(g,weights,cactus::product(g,input_vec,cactus::product(g,delta_assgin,rate))));
    auto bias_assgin = cactus::assign(g,bias,cactus::add(g,bias,cactus::product(g,rate,delta)));
    g.run(g.initAllVariable());
    for (int i = 0; i < 10;i++) {
        for (int j = 0; j < 4;j++) {
            g.run(weights_assgin, { { "input",{iv[j][0],iv[j][1]} },{ "label",labels[j] } });
            g.run(bias_assgin, { { "input",{ iv[j][0],iv[j][1] } },{ "label",labels[j] } });
            std::cout << input_vec << label << activator << weights<< bias << std::endl;
            
        }
    }
    g.run(activator, { { "input",{ 1,1 } } });
    std::cout << activator << std::endl;
    g.run(activator, { { "input",{ 1,0 } } });
    std::cout << activator << std::endl;
    g.run(activator, { { "input",{ 0,1 } } });
    std::cout << activator << std::endl;
    return 0;
}