#ifndef CACTUS_PERCEPTRON_HPP
#define CACTUS_PERCEPTRON_HPP

#include <iostream>
#include <Eigen/Core>
namespace cactus {
	typedef int(*sigmal)(double_t);
	
	template<typename T ,uint16_t num>
	class Perceptron {
	public:
		Perceptron(sigmal activator):weights(num) {
			this->activator = activator;
			weights.setOnes();
			bias = 0;
		}
		int predict(Eigen::ArrayXd input_vec) {
			assert(input_vec.size() == num);
			return activator((weights*input_vec).sum() + bias);
		}
		friend std::ostream& operator <<(std::ostream& os, Perceptron& p) {
			os << p.weights;
			return os;
		}
	private:
		int updateWeights(Eigen::ArrayXd input_vec, double_t output, double_t label, double_t rate) {
			double_t delta = label - output;

		}
		
	private:
		sigmal activator;
		Eigen::ArrayXd weights;
		double_t bias;
	};
}

#endif // !CACTUS_PERCEPTRON_HPP

