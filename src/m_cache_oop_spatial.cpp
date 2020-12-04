#include "ScopedTimer.h"
#include <vector>
#include <list>
#include <numeric>   //std::iota
#include <algorithm> //std::accumulate
#include <iostream>

class Slow {
public:            double compute() const { return d2 * d9 + d5 * d4; }
private:
    double d2 = 2;
    double darray1[128];
    double d9 = 9;
    double d4 = 4;
    double darray2[128];
    double d5 = 5;
};

class Fast {
public:         double compute() const { return d2 * d9 + d5 * d4; }
private:
    double darray1[128];    double darray2[128];
    double d2 = 2;          double d9 = 9;
    double d4 = 4;          double d5 = 5;
};

int main()
{
    constexpr std::size_t nb_elem = 500'000;
    constexpr std::size_t repeat = 500;

    std::vector<Fast> vecFast(nb_elem);
    std::vector<Slow> vecSlow(nb_elem);
    auto lambda_acc = [](double a, const auto &b) { return a + b.compute(); };

    double sum_slow = 0;
    for (std::size_t i = 0 ; i < repeat; ++i){
        cache::ScopedTimer timer1("Time using the Slow class\t");
        sum_slow = std::accumulate(vecSlow.begin(), vecSlow.end(), 0, lambda_acc);
    }
    
    double sum_fast = 0;
    for (std::size_t i = 0 ; i < repeat; ++i){
        cache::ScopedTimer timer1("Time using the Fast class\t");
        sum_fast = std::accumulate(vecFast.begin(), vecFast.end(), 0, lambda_acc);
    }
    std::cout << sum_slow << " " << sum_fast << " " << Fast().compute() << std::endl;
}