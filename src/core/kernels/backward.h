#include "framework/node.hpp"
#include "framework/graph.hpp"
#include "compute.h"

namespace cactus {
    
    
    Output backward(Graph & g, Input x);
    Output grad(Graph & g, Input dy,Input x);
}
