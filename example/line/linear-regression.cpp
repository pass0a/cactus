#include <iostream>
#include "cactus.hpp"


int main() {
    unsigned int num_inputs = 2;
    unsigned int num_examples = 1000;
    cactus::Graph g;
    auto true_w = cactus::Const(g,{ 2,3 } );
    auto true_b = true_w + 3;
    /*auto true_b = cactus::Const(g, 4.2);
    auto features = cactus::Random(g,cactus::kDouble, { num_inputs,num_examples });
    auto init=g.initAllVariable();*/
    std::cout << true_w.tensor().shape().rows <<":"<< true_w.tensor().shape().cols << std::endl;
    g.run(true_b);
    std::cout << true_b << std::endl;
    return 0;
}