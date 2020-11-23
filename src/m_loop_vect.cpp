
#include "ScopedTimer.h"
#include "f_loop_vect.h"
#include <algorithm>

int main()
{
    constexpr int size_array = 100000;
    int a1[size_array], b1[size_array], c1[size_array];

    std::fill(a1, a1 + size_array, 0);
    std::fill(b1, b1 + size_array, 0);
    std::fill(c1, c1 + size_array, 0);

    {
        cache::ScopedTimer("No vectorization:\t");
        vect::sum_no_vec(a1,b1,c1,size_array);
    }

    int a2[size_array], b2[size_array], c2[size_array];
    std::fill(a2, a2 + size_array, 0);
    std::fill(b2, b2 + size_array, 0);
    std::fill(c2, c2 + size_array, 0);

    {
        cache::ScopedTimer("With vectorization:\t");
        vect::sum_vec(a2,b2,c2,size_array);
    }

    for (int i = 0; i < size_array; ++i)
    {
        if (a1[i] != a2[i] || b1[i] != b2[i] || c1[i] != c2[i])
        {
            std::cout << "Error" << std::endl;
            return 1;
        }
    }
}