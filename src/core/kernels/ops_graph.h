#include "../framework/node.hpp"

namespace cactus {
class InitVariable : public Operation {
  public:
      InitVariable(std::vector<Node *> l) { inputs = l; }
    void compute() {
        for (auto n : inputs) {
            switch (n->type()) {
            case NtVariable:
                n->compute();
                break;
            default:
                break;
            }
        }
    }
    NodeType type() { return NtInitOp; }
};

} // namespace cactus
