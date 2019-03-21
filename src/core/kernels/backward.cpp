#include "backward.h"
#include "compute.h"
#include <map>
#include <queue>

namespace cactus {
    class Xgrad :public Node {
    public:
        NodeType type();
        Xgrad();
        void grad(Node* np, Tensor val);
        xgrads grad();
    private:
        Node* ptr;
    };
    class BackwardOp :public Operation {
    public:
        NodeType type();
        BackwardOp(Input& x);
        void compute();
        Output pick(Node* idx);
    private:
        std::map<Node*, Xgrad> xr;
    };

    class GradPickOp :public Operation {
    public:
        GradPickOp(Input x, Input y);
        void compute();
    };

    NodeType Xgrad::type() { return NtConst; }
    Xgrad::Xgrad() :ptr(NULL) {
    }
    void Xgrad::grad(Node* np, Tensor val) {
        if (ptr) {
            t = add_impl(t, val);
        }
        else {
            ptr = np;
            t = val;
        }

    }
    xgrads Xgrad::grad() {
        return ptr->grad(t);
    }

    NodeType BackwardOp::type() { return NtGradOp; }
    BackwardOp::BackwardOp(Input& x) {
        inputs = { x.node() };
    }
    void BackwardOp::compute() {
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
    Output BackwardOp::pick(Node* idx)
    {
        auto it = xr.find(idx);
        if (it != xr.end()) {
            return Output(&it->second);
        }
        return Output();
    }

    GradPickOp::GradPickOp(Input x, Input y) {
        inputs = { x.node(),y.node() };
    }
    void GradPickOp::compute() {
        if (inputs[0]->type() == NtGradOp) {
            t = ((BackwardOp*)inputs[0])->pick(inputs[1]).tensor();
        }
    }
    Output backward(Graph & g, Input x) {
        return g.insert(std::make_shared<BackwardOp>(x));
    }
    Output grad(Graph & g, Input dy, Input x)
    {
        return g.insert(std::make_shared<GradPickOp>(dy, x));
    }
}