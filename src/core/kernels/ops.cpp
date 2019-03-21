#include "ops.hpp"
#include <Eigen/Dense>
namespace cactus {
    class NodeRandom : public Node {
    private:
        DataType dt;
        Shape s;
    public:
        NodeRandom(Shape _s, DataType _dt):dt(_dt),s(_s) {
        }
        NodeType type() { return NtVariable; }
        template<typename T>
        void compute() {
            Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ret;
            ret.setRandom(s.rows,s.cols);
            t = Tensor(DataTypeToEnum<T>::value, { (std::size_t)ret.rows(),(std::size_t)ret.cols() });
            t.assign(ret.data(), ret.size() * sizeof(T));
        }
        void compute() {
            CASES(dt,compute<T>());
        }
    };
    Output Const(Graph& g, const Initializer& v) {
        return g.insert(std::make_shared<NodeConst>(v.tensor));
    }
    Output Variable(Graph& g, const Initializer& v) {
        return g.insert(std::make_shared<NodeVariable>(v.tensor));
    }
    Output Placeholder(Graph& g, DataType dt, Shape s) {
        return g.insert(std::make_shared<NodePlaceholder>(s, dt));
    }
    Output Random(Graph& g, DataType dt, Shape s) {
        return g.insert(std::make_shared<NodeRandom>(s, dt));
    }
}
