
#include "../framework/graph.hpp"

namespace cactus {
    Output Cx_EXPORTS backward(Graph & g, Input x);
    Output Cx_EXPORTS grad(Graph & g, Input dy, Input x);
}
