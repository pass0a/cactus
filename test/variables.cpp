#include "../../../3rd/eigen/Eigen/Dense"
#include <gtest/gtest.h>
#include <vector>
using namespace Eigen;

template<typename Tx, typename Ty>
struct S {
    auto operator()() { return (Tx)0+(Ty)0; }
};
template<typename LV, typename RV>
std::vector<typename std::result_of<S<LV, RV>()>::type> powt1(std::vector<LV> x, std::vector<RV> y) {
    using ret_type = typename std::result_of<S<LV, RV>()>::type;
    std::vector<ret_type> tmp(x.size());
    Map<Array<LV, Dynamic, RowMajor>>  v2(x.data(), x.size());
    Map<Array<RV, Dynamic, RowMajor>>  v3(y.data(), y.size());
    Map<Array<ret_type, Dynamic, RowMajor>> z(tmp.data(),x.size());
    z=pow(v2, v3);
    return tmp;
}
template<typename LV, typename RV>
std::vector<typename std::result_of<S<LV, RV>()>::type> powt(std::vector<LV> x,RV y){
    std::vector<typename std::result_of<S<LV, RV>()>::type> t;
    t.push_back(y);
    return powt1(x,t);
}

TEST(layer, fully) {
    std::vector<double> v2 = { 1.2,2,3,4 };
    std::vector<int> v3 = { 1,2,3,4 };
    std::complex<float> p(2.0f);
    std::vector<std::complex<float>> tmp = { (1.0f,2.0f) };
    auto z = powt(tmp,2.0f);
    std::cout << z[0] << std::endl;
    //powt(tmp, 2);
    /*auto z1 = powt(v2, 3);
    std::cout << z1 << std::endl;*/
}