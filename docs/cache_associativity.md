---
title: Cache associativity
---

When loading data in memory, cache slots needs to be mapped to memory chunks. 

Ideally, it would be possible to map each cache slots to every memory chunk. Such a mapping is called a __fully associative cache__. Such a cache is very flexible but fully associative caches are costly to implement in the hardware. In practice, there are restrictions on where a cache slot can be loaded in memory (__direct mapped cache__ or __N-way associative cache__).  

To illustrate this, we re-run the code used in the L1/L2/L3 experiment, but this time we different steps.

```cpp
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
```

Here are the results :

![Example of cache associativity impact. Light blue point are individual run time for the `touch every` function with size_array=16000 and nb_touch=1024*1024. Darkblue point are average run-time per step over 100 experiments. Vertical line shows steps which are multiple of 128.](m_cache_associativity.png)

Running a million `touch` on an array containing `16000 int` takes between 2 and 3 milliseconds for most `step`. We observe a decrease in performance for case where the `step` is a multiple of 128. In these cases, due to cache associativity, several values are competing for the same cache slot when they are loaded in memory, slow down the communication between the cache and the CPU memory chunks.

Note : this effect is usually recognized as anecdotal. It took me some time before understanding what was going on, and I had to _calibrate_ the size of the array to make the _cache associativity effect_ clearly visible. In particular, I you intend to play with this, make sure you array fills at least the L1 cache to see these communication effects...

For more details, see example 5 in [Igor Ostrovsky's blog pos](http://igoro.com/archive/gallery-of-processor-cache-effects/). In [this CppCon video](https://youtu.be/BP6NxVxDQIs?t=1401), Tim Doumler give an intuitive understanding of what's going on.


 | --------------------------------- | --------------------------------- | --------------------------------- |
|:--|:--:|--:|
| [Prev page](l1_l2.html) | [Main page](index.html) | [Next page](todo.html) |

