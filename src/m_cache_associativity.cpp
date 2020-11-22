#include "ScopedTimer.h"
#include <vector>
#include <sstream>

void touch_every_step(int *array, std::size_t array_size, std::size_t step)
{
    constexpr std::size_t nb_access = 10000;
    int accessor = 0;
    for (std::size_t repeat = 0; repeat < nb_access; ++repeat)
    {
        ++array[accessor];
        accessor = (accessor + step) % array_size;
    }
}

void scoped_touch_every_step(int *array, std::size_t array_size, std::size_t step)
{
    cache::ScopedTimer timer;
    touch_every_step(array, array_size, step);
    std::cout << "Step: " << step
              << "; Size: " << array_size
              << "; Time: " << timer.elapsed_ms() << " ms\n" ;
}

int main()
{

    constexpr std::size_t max_step = 1200;
    constexpr std::size_t nb_reprod = 15;
    /*
    const std::vector<std::size_t> array_sizes{8,16,32,64,128,512};
    for (const auto array_size : array_sizes){
                int *array = new int[array_size*1024];
        for (std::size_t step = 0; step < max_step; ++step)
            for (std::size_t reprod = 0; reprod < nb_reprod; ++reprod)
                scoped_touch_every_step(array, array_size*1024, step);
    }
    return 0;*/

    {
        constexpr std::size_t array_size = 1024*15;
        int *array = new int[array_size];
        for (std::size_t step = 0; step < max_step; ++step)
            for (std::size_t reprod = 0; reprod < nb_reprod; ++reprod)
                scoped_touch_every_step(array, array_size, step);
        //delete[] array;
    }

    {
        constexpr std::size_t array_size = 1024*16;
        int *array = new int[array_size];
        for (std::size_t step = 0; step < max_step; ++step)
            for (std::size_t reprod = 0; reprod < nb_reprod; ++reprod)
                scoped_touch_every_step(array, array_size, step);
    }
        {
        constexpr std::size_t array_size = 1024*17;
        int *array = new int[array_size];
        for (std::size_t step = 0; step < max_step; ++step)
            for (std::size_t reprod = 0; reprod < nb_reprod; ++reprod)
                scoped_touch_every_step(array, array_size, step);
    }

    {
        constexpr std::size_t array_size = 1024 * 31;
        int *array = new int[array_size];
        for (std::size_t step = 0; step < max_step; ++step)
            for (std::size_t reprod = 0; reprod < nb_reprod; ++reprod)
                scoped_touch_every_step(array, array_size, step);
    }

    {
        constexpr std::size_t array_size = 1024 * 32;
        int *array = new int[array_size];
        for (std::size_t step = 0; step < max_step; ++step)
            for (std::size_t reprod = 0; reprod < nb_reprod; ++reprod)
                scoped_touch_every_step(array, array_size, step);
    }

    {
        constexpr std::size_t array_size = 1024 * 33;
        int *array = new int[array_size];
        for (std::size_t step = 0; step < max_step; ++step)
            for (std::size_t reprod = 0; reprod < nb_reprod; ++reprod)
                scoped_touch_every_step(array, array_size, step);
    }

    {
        constexpr std::size_t array_size = 1024 * 512;
        int *array = new int[array_size];
        for (std::size_t step = 0; step < max_step; ++step)
            for (std::size_t reprod = 0; reprod < nb_reprod; ++reprod)
                scoped_touch_every_step(array, array_size, step);
    }
    std::cout << std::flush;
}