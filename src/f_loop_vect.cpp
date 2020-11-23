#include "f_loop_vect.h"

namespace vect
{
    void sum_no_vec(int *a1, int *b1, int *c1, int array_size)
    {
        for (int i = 0; i < array_size - 1; ++i)
        {
            a1[i] += b1[i];
            b1[i + 1] += c1[i];
        }
    }
    void sum_vec(int *a2, int *b2, int *c2, int array_size)
    {
        a2[0] += b2[0];
        for (int i = 1; i < array_size - 1; ++i)
        {
            a2[i] += b2[i];
            b2[i + 1] += c2[i];
        }
        b2[array_size - 1] += c2[array_size - 1];
    }
} // namespace vect