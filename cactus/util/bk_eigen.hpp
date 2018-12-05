#ifndef CACTUS_BK_EIGEN_HPP
#define CACTUS_BK_EIGEN_HPP

#include "../3rd/eigen/Eigen/Dense"
namespace cactus {
    using namespace Eigen;
    class bk_eigen {
    public:
        template<typename Tx,typename Ty>
        Tx matmul(Tx x,Ty y){
            //assert(x.shape()[0] > 0);
            //assert(y.shape()[0] > 0);
            size_t xx,xy,yx,yy;
            xx = x.shape()[0];
            yx = y.shape()[0];
            (x.dim() == 1) ? xy = 1 : xy = x.shape()[1];
            (y.dim() == 1) ? yy = 1 : yy = y.shape()[1];

            Map<Matrix<Tx::value_type, Dynamic, Dynamic, RowMajor>>
                a(x.data(), xx,xy),b(y.data(),yx,yy);
            std::cout << a*b << std::endl;
            return x;
            
        }

    };
}
#endif