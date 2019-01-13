#include <iostream>
#include <vector>
#include <memory>
template<typename Tx,typename Ty>
struct S {
    auto operator()() { Tx x; Ty y; return x + y; }
};

int main() {
    std::result_of<S<int,int>()>::type x=1.3;
    std::cout << x << std::endl;
    return 0;
}