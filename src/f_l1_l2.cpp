#include "f_l1_l2.h"

namespace cache
{
    void touch_every(int *array, int size_array, int nb_touch, int step)
    {
        const int lengthMod = (size_array-1);
        for (int touch = 0; touch < nb_touch; touch++)
            array[(touch * step) & lengthMod]++;
    }
} 