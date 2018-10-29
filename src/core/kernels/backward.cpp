#include "backward.h"
#include <queue>
namespace cactus {
    class Xgrad :public Node {
    public:
        NodeType type() { return NtConst; }
        Xgrad() :ptr(NULL) {
        }
        void grad(Node* np, Tensor val) {
            if (ptr) {
                t = add(t, val);
            }
            else {
                ptr = np;
                t = val;
            }

        }
        xgrads grad() {
            return ptr->grad(t);
        }
    private:
        Node* ptr;
    };
    class BackwardOp :public Operation {
    public:
        NodeType type() { return NtGradOp; }
        BackwardOp(Input& x) {
            inputs = { x.node() };
        }
        void compute() {
            xr.clear();
            Node* parent = inputs[0];
            std::queue<Node*> list;
            xgrads l;
            list.push(parent);
            xr[parent].grad(parent, 1);

            while (!list.empty()) {
                parent = list.front();
                l = xr[parent].grad();
                list.pop();
                for (auto n : l) {
                    xr[n.first].grad(n.first, n.second);
                    list.push(n.first);
                }
            }

            t = 1;
        }
        Output pick(Node* idx)
        {
            auto it = xr.find(idx);
            if (it != xr.end()) {
                return Output(&it->second);
            }
            return Output();
        }
    private:
        std::map<Node*, Xgrad> xr;
    };
    
    class GradPickOp:public Operation {
    public:
        GradPickOp(Input x,Input y) {
            inputs = { x.node(),y.node() };
        }
        void compute() {
            if (inputs[0]->type() == NtGradOp) {
                ((BackwardOp*)inputs[0])->pick(inputs[1]);
            }
        }
    };
    Output backward(Graph & g, Input x) {
        return g.insert(std::make_shared<BackwardOp>(x));
    }
    Output grad(Graph & g,Input dy, Input x)
    {
        return g.insert(std::make_shared<GradPickOp>(dy,x));
    }
}
