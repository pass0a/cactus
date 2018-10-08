#include "ops_graph.h"
namespace cactus {

InitVariable::InitVariable(std::vector<Node *> l) { inputs = l; }
void InitVariable::compute() {
    for (auto n : inputs) {
      switch(n->type()){
      case NtVariable:
        n->compute();
        break;
      default:
        break;
      }
    }
}
} // namespace cactus
