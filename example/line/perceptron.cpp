#include <iostream>
#include <vector>
#include <memory>
template<typename Tx,typename Ty>
struct S {
    auto operator()(Tx,Ty) { return 1.0; }
};

int main() {
    std::result_of<S<int,int>(int,int)>::type x = 0.4;
    std::cout << x << std::endl;
    return 0;
}