#include "ScopedTimer.h"
#include <vector>
#include <sstream>

constexpr std::size_t nb_elem = 513 * 1024 * 1024;
std::vector<char> vec_char(nb_elem);
std::vector<short> vec_short(nb_elem);
std::vector<int> vec_int(nb_elem);
std::vector<float> vec_float(nb_elem);
std::vector<double> vec_double(nb_elem);

template <typename T>
void touch_every_step(std::size_t delta, const std::string &type, T &vec)
{
    std::ostringstream message;
    message << "Touching every " << delta << " index on type " << type << " ";
    std::string m{message.str()};
    cache::ScopedTimer timer(m.c_str());
    for (std::size_t i = 0; i < 1024 * 1024; i++)
        vec[i * delta] += 1;
}

int main()
{
    constexpr std::size_t nb_repeat = 1;
    constexpr std::size_t max_step = 512;
    for (std::size_t repeat = 0; repeat < nb_repeat; ++repeat)
        for (std::size_t step = 0; step <= max_step; ++step)
        {
            touch_every_step(step, "char", vec_char);
            touch_every_step(step, "short", vec_short);
            touch_every_step(step, "int", vec_int);
            touch_every_step(step, "double", vec_double);
        }
}