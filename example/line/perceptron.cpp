#include <iostream>
#include <complex>
#include <vector>
#include "../../cactus/cactus.hpp"

#define PI 3.1415

inline std::complex<double> omega(const int& n, const int& k,bool inverse) {
    if (!inverse) return std::complex<double>(cos(2 * PI / n * k), sin(2 * PI / n * k));
    return conj(std::complex<double>(cos(2 * PI / n * k), sin(2 * PI / n * k)));
}

inline void fft(std::vector<std::complex<double>>& s,bool inverse) {
    if (s.size() == 1) return;
    std::vector<std::complex<double>> tmp(s.size()),a1(s.size()>>1),a2(s.size() >> 1);

    auto m = s.size() >> 1;

    for (int i = 0; i < m; ++i) {
        tmp[i] = s[i << 1];
        tmp[i + m] = s[i << 1 | 1];
    }
    auto iter=tmp.begin();
    std::copy(iter, iter+m, a1.begin());
    std::copy(iter + m, iter+m+m, a2.begin());
    fft(a1, inverse);
    fft(a2, inverse);
    for (int i = 0; i < m; ++i) {
        auto t = omega(s.size(), i, inverse);
        tmp[i] = a1[i] + t * a2[i];
        tmp[i + m] = a1[i] - t * a2[i];
    }
    std::copy(tmp.begin(),tmp.end() , s.begin());
    return;
}

inline void fft2(std::vector<std::complex<double>>& s, bool inverse) {
    int lim = 0,n=s.size();
    while ((1 << lim) < n) lim++;
    for (int i = 0; i < n; i++) {
        int t = 0;
        for (int j = 0; j < lim; j++)
            if ((i >> j) & 1) t |= (1 << (lim - j - 1));
        if (i < t) swap(s[i], s[t]); // i < t 的限制使得每对点只被交换一次（否则交换两次相当于没交换）
    }
    return;
}


typedef class FastFourierTransform {
    std::vector<std::complex<double>> omega, omegaInverse;
public:
    void init(size_t n) {
        omega.resize(n);
        omegaInverse.resize(n);
        for (size_t i = 0; i < n; ++i) {
            omega[i] = std::complex<double>(cos(2 * PI / n * i), sin(2 * PI / n * i));
            omegaInverse[i] = conj(omega[i]);
        }
    }

    void transform(std::vector<std::complex<double>>& s) {
        size_t n = s.size();
        init(s.size());
        for (int i = 0, j = 0; i < s.size(); ++i) {
            if (i > j)  std::swap(s[i], s[j]);
            for (int l = s.size() >> 1; (j ^= l) < l; l >>= 1);
        }

        for (size_t l = 2; l <= n; l <<= 1) {
            size_t m = l / 2;
            for (auto p = s.begin(); p != s.end()-1;p++) {
                for (int i = 0; i < m; ++i) {
                    std::complex<double> t = omega[n / l * i] * p[m + i];
                    p[m + i] = p[i] - t;
                    p[i] += t;
                }
            }
        }
    }

    /*void dft(Complex *a, const int& n) {
        transform(a, n, omega);
    }

    void idft(Complex *a, const int& n) {
        transform(a, n, omegaInverse);
        for (int i = 0; i < n; ++i) a[i] /= n;
    }*/
} libfft;

int main() {
    using namespace cactus;
    std::vector<std::complex<double>> tmp = {5,3,8,9,4};
    fft2(tmp,false);
    return 0;
}

