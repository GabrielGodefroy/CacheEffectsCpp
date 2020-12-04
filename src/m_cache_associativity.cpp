#include "ScopedTimer.h"
#include "DoNotOptimize.hpp"
#include "f_l1_l2.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <sstream>

constexpr std::size_t nb_touch = 1024 * 1024;
constexpr int size = 4000; //8192; //32 MB
constexpr std::size_t nb_repeat = 96;

void scoped_touch_every(int *vec_ptr, int step)
{
    auto r = cache::touch_every(vec_ptr, size, nb_touch, step);
    cache::DoNotOptimize(r);
}

int main()
{
    //int *vec_ptr = new int[size];
    int vec_ptr[size];
    std::iota(vec_ptr, vec_ptr + size, 0);
    for (std::size_t repeat = 0; repeat < nb_repeat; repeat++)
        for (std::size_t step = 100; step < 150; step++)
        {
            cache::ScopedTimer timer;
            scoped_touch_every(vec_ptr, step);
            std::cout << step << "\t" << timer.elapsed_second() << std::endl;
        }
    //delete[] vec_ptr;
}