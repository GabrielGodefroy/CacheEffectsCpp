#include "f_l1_l2.h"

namespace cache
{
    void touch_every(int *array, int size_array, int nb_touch)
    {
        for (int i = 0; i < nb_touch; i++)
            array[(i * 32) & (size_array-1)]++;
    }
} 