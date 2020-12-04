#include <vector>
#include <sstream>
#include <memory>
#include <numeric>

#include "ScopedTimer.h"
#include "DoNotOptimize.hpp"
#include "f_l1_l2.h"

constexpr std::size_t nb_touch = 256 * 1024 * 1024;
constexpr std::size_t nb_repeat = 16;
constexpr std::size_t step = 128;

void scoped_touch_every(const std::size_t nb_elem)
{
    int *vec_ptr = new int[nb_elem];
    std::iota(vec_ptr, vec_ptr + nb_elem, 0);
    cache::DoNotOptimize(vec_ptr);
    cache::ScopedTimer timer;
    cache::DoNotOptimize(timer.elapsed_second());
    auto r = cache::touch_every(vec_ptr, nb_elem, nb_touch, step);
    cache::DoNotOptimize(r);
    std::cout << sizeof(int[nb_elem]) << "\t" << timer.elapsed_second() << std::endl;
    delete[] vec_ptr;
}

int main()
{
    for (std::size_t repeat = 0; repeat < nb_repeat; repeat++)
        for (std::size_t nb_elem = 64; nb_elem < 1024 * 1024 * 256; nb_elem *= 2)
        {
            scoped_touch_every(nb_elem);
        }
}