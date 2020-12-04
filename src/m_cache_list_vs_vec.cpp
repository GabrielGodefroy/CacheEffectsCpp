#include "ScopedTimer.h"
#include "DoNotOptimize.hpp"
#include <vector>
#include <list>
#include <numeric>   //std::iota
#include <algorithm> //std::accumulate
#include <iostream>

/*! \brief Prevent instruction re-ordering 
 *  \see https://stackoverflow.com/questions/37786547/enforcing-statement-order-in-c 
 */
template <class T>
__attribute__((always_inline)) inline void DoNotOptimize(const T &value) {
  asm volatile("" : "+m"(const_cast<T &>(value)));
}
constexpr std::size_t nb_elem = 1'000'000;
typedef int DataType;

int main()
{
    std::vector<DataType> vec(nb_elem);
    std::iota(vec.begin(), vec.end(), 0);

    std::list<DataType> list(nb_elem);
    std::iota(list.begin(), list.end(), 0);

    double tvec, tlist = 0;
    DataType sum_vec, sum_list = 0;
    {
        cache::ScopedTimer timer2("Time to sum the elements of a std::list:\t");
        sum_list = std::accumulate(list.begin(), list.end(), sum_list);
        cache::DoNotOptimize(sum_list);
        tlist = timer2.elapsed_ms();
    }
    {
        cache::ScopedTimer timer1("Time to sum the elements of a std::vector:\t");
        sum_vec = std::accumulate(vec.begin(), vec.end(), sum_vec);
        cache::DoNotOptimize(sum_vec);
        tvec = timer1.elapsed_ms();
    }
    std::cout <<"Ratio:\t" << tlist / tvec << std::endl;
}