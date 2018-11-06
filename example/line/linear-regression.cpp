#include <iostream>
#include "cactus.hpp"


int main() {
    unsigned int num_inputs = 2;
    unsigned int num_examples = 1000;
    cactus::Graph g;
    auto true_w = cactus::Const(g, { 2,-3.4 });
    auto true_b = cactus::Const(g, 4.2);
    auto features = cactus::Random(g,cactus::kDouble, { num_inputs,num_examples });
    auto init=g.initAllVariable();
    g.run(init);
    std::cout << features << std::endl;
    return 0;
}