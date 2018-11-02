
#include "../framework/graph.hpp"

namespace cactus {
    Output backward(Graph & g, Input x);
    Output grad(Graph & g, Input dy, Input x);
}
