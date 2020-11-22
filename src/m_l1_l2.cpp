//#include <vector>
//#include "ScopedTimer.h"
//#include <sstream>

/*constexpr std::size_t nb_touch = 32 * 1024 * 1024;

void scoped_touch_every(const std::size_t nb_elem)
{
    std::vector<int> vec_int(nb_elem, 0);
    const std::size_t lengthMod = nb_elem - 1;

    //cache::ScopedTimer timer;

    for (std::size_t i = 0; i < nb_touch; i++)
    {
        vec_int[(i * 16) % lengthMod] += 3;
    }

    //std::cout << nb_elem << "\t" << timer.elapsed_second() / (nb_touch) << std::endl;
}
*/
int main()
{
    int alpha{11};
    int beta = 22;
    constexpr int zeta = 33;
    const int deta = 44;
    return alpha+beta*zeta+deta;
    //scoped_touch_every(std::size_t{4});
    /*scoped_touch_every(std::size_t{4});
    scoped_touch_every(std::size_t{4});

    scoped_touch_every(std::size_t{5});
    scoped_touch_every(std::size_t{5});
    scoped_touch_every(std::size_t{5});*/
}