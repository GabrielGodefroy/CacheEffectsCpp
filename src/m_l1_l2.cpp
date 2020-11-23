#include <vector>
#include <sstream>
#include <memory>

#include "ScopedTimer.h"
#include "f_l1_l2.h"

constexpr std::size_t nb_touch = 6400000;

void scoped_touch_every(const std::size_t nb_elem)
{

    std::vector<int> vec_int(nb_elem, 0);
    const std::size_t lengthMod = nb_elem - 1;

    cache::ScopedTimer timer;

    cache::touch_every(vec_int.data(), vec_int.size(), nb_touch);
    
    std::cout << nb_elem << "\t" << timer.elapsed_second() << std::endl;
}

int main()
{
    for(std::size_t nb_elem = 4; nb_elem < 1024;++nb_elem)
        scoped_touch_every(nb_elem);
}