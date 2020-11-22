#include "ScopedTimer.h"
#include <vector>
#include <sstream>
#include "f_cache_lines.hpp"

constexpr std::size_t nb_touch = 1024 * 1024;
constexpr std::size_t nb_elem = 256 * nb_touch;
std::vector<char> vec_char(nb_elem);
std::vector<short> vec_short(nb_elem);
std::vector<int> vec_int(nb_elem);
std::vector<double> vec_double(nb_elem);

template <typename T>
void scoped_touch_every_step(std::vector<T> &vec_elem, std::size_t delta, const std::string &type)
{
    std::ostringstream message;
    message << "Touching every " << delta << " index on type " << type << " ";
    std::string m{message.str()};
    cache::ScopedTimer timer(m.c_str());
    cache::touche_every_step(vec_elem, delta, nb_touch);
}

int main()
{
    constexpr std::size_t max_step = 200;
    constexpr std::size_t nb_repeat = 25;
    for (std::size_t repeat = 0; repeat < nb_repeat; ++repeat)
        for (std::size_t step = 0; step <= max_step; ++step)
        {
            scoped_touch_every_step<char>(vec_char, step, "char");
            scoped_touch_every_step<short>(vec_short, step, "short");
            scoped_touch_every_step<int>(vec_int, step, "int");
            scoped_touch_every_step<double>(vec_double, step, "double");
        }
}