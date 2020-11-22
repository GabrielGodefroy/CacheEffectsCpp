#pragma once
#include <vector>
#include <assert.h>
namespace cache
{
    template <typename T>
    void touche_every_step(
        std::vector<T>& vecElem, 
        std::size_t delta, 
        std::size_t nb_touch)
    {  
        assert(nb_touch*delta < vecElem.size());
        for (std::size_t i = 0; i < nb_touch; i++)
            vecElem[i * delta] += 1;
    }
} // namespace cache