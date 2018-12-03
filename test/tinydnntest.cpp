#include <gtest/gtest.h>
#include "tiny_dnn/tiny_dnn.h"

using namespace tiny_dnn;
TEST(core, xtensor) {
    fully_connected_layer l(4, 2);
    EXPECT_EQ(l.in_channels(), 3u);  // in, W and b

    l.weight_init(weight_init::constant(1.0));
    l.bias_init(weight_init::constant(0.5));

    vec_t in = { 0, 1, 2, 3 };
    std::vector<const tensor_t *> o;
    l.forward({ { in } }, o);
    vec_t out = (*o[0])[0];
    vec_t out_expected = { 6.5, 6.5 };  // 0+1+2+3+0.5

    for (size_t i = 0; i < out_expected.size(); i++) {
        EXPECT_FLOAT_EQ(out_expected[i], out[i]);
    }
}