#include <iostream>
#include "ScopedTimer.h"
#include <memory>
#include <limits>
#include <algorithm>
#include <numeric>

int main()
{


    constexpr unsigned int size_array = 1024 * 1024;
    double *array = new double[size_array];
    constexpr double multiplier = 2.1;
    std::iota(array, array + size_array, 1.5);

    {
        cache::ScopedTimer t("Sum on every elements\t\t");
        for (unsigned int it = 0; it < size_array; ++it)
            array[it] *= multiplier;
    }

    {
        cache::ScopedTimer t("Sum on every 16th elements\t");
        for (unsigned int it = 0; it < size_array; it += 8)
            array[it] *= multiplier;
    }

    {
        cache::ScopedTimer t("Compute on every elements\t");
        for (unsigned int it = 0; it < size_array; ++it)
            array[it] += double(char(std::hash<double>{}(array[it]))+1.5);
    }

    {
        cache::ScopedTimer t("Compute on every 16th elements\t");
        for (unsigned int it = 0; it < size_array; it += 8)
            array[it] += double(char(std::hash<double>{}(array[it]))+1.5);
    }

    delete array;
}