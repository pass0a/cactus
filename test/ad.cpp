
#include <cmath>
#include <vector>
#include <iostream>
#include <Eigen/Dense>

namespace SAD  // Simple Automatic Differentiation
{
    class ADV
    {
    public:
        ADV(double v = 0, double d = 0);

        // overloaded unary and binary operators
        ADV operator + (const ADV &x) const;
        ADV operator - (const ADV &x) const;
        ADV operator * (const ADV &x) const;
        friend ADV sin(const ADV &x);
        friend ADV cos(const ADV &x);

        double val;  // value of the variable
        double dval;  // derivative of the variable
    };

    ADV::ADV(double v, double d) : val(v), dval(d) {}

    ADV ADV::operator+(const ADV &x) const
    {
        ADV y;
        y.val = val + x.val;
        y.dval = dval + x.dval;
        return y;
    }

    ADV ADV::operator-(const ADV &x) const
    {
        ADV y;
        y.val = val - x.val;
        y.dval = dval - x.dval; // sum rule
        return y;
    }

    ADV ADV::operator*(const ADV &x) const
    {
        ADV y;
        y.val = val*x.val;
        y.dval = x.val*dval + val*x.dval; // product rule
        return y;
    }

    ADV sin(const ADV &x)
    {
        ADV y;
        y.val = std::sin(x.val);
        y.dval = std::cos(x.val)*x.dval; // chain rule
        return y;
    }

    ADV cos(const ADV &x)
    {
        ADV y;
        y.val = std::cos(x.val);
        y.dval = -std::sin(x.val)*x.dval; // chain rule
        return y;
    }
}

void test() {
    using namespace SAD;
    using namespace std;

    static const double PI = 3.1415926;
    vector<ADV> x;

    x.emplace_back(3, 0);
    x.emplace_back(4, 1);

    ADV y1 = x[0]*x[0];
    ADV y2 = x[1] + 2;
    ADV z1 = y1*x[1] + y2;

    cout << "x = [" << x[0].val << ", " << x[1].val << "]" << endl;
    cout << "z = [" << z1.val << ", " << y2.val << "]" << endl;
    cout << "[dz1/dx0, dz2/dx0] = [" << z1.dval << "," << y2.dval << "]" << endl;
}

template<typename T>
T wrap_log(T val) {
    return log(val);
}

int main()
{
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> x(2,2);
    Eigen::ArrayXi y(5);
    x << 1, 2, 3, 4;
    y << 2, 3, 4, 5, 6;
    
    
}