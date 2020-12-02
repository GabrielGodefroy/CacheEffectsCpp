---
title: A gallery C++ of cache effects
author: Gabriel Godefroy
---

Hardware effects impact performances. This repository contains C++ codes illustrating some of these effects, as well as Python code to plot the results. You can fork this repository and try to reproduce the results, as these performance tests are hardware dependent.

This repository, and all the contained examples, are strongly inspired by:

 * [“Gallery of Processor Cache Effects“, by Igor Ostrovsky](http://igoro.com/archive/gallery-of-processor-cache-effects/)
 * [“Want fast C++? Know your hardware!“, by Timur Doumler](https://www.youtube.com/watch?v=BP6NxVxDQIs)

### Results:

For each effect, the codes and results are presented in the following pages:

 * [__Memory alignement and padding__](alignement.html): For a CPU to work efficiently, there are restrictions on the addresses where objects of types are located in memory (_alignment_). In order to respect these alignements, the compiler sometimes needs to insterts extra bytes (_padding_) between the the members of user_defined types. This impact memory consumption...

## Impact of cache lines

```cpp
{{src/f_cache_lines.hpp}}
```


![The impact of cache lines on ](m_cache_lines.png)


## L1, L2 and L3 caches

```txt
Architecture:          x86_64
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                4
On-line CPU(s) list:   0-3
Thread(s) per core:    2
Core(s) per socket:    2
NUMA node(s):          1
Vendor ID:             GenuineIntel
Model name:            Intel(R) Core(TM) i7-4510U CPU @ 2.00GHz
Stepping:              1
Virtualization:        VT-x
L1d cache:             32K
L1i cache:             32K
L2 cache:              256K
L3 cache:              4096K
```



## Cache associativity

![The impact of cache lines on cache associativity](m_cache_associativity.png)
![The impact of cache lines on cache associativity](m_cache_associativity_zoom.png)