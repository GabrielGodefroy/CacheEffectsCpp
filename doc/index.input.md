---
title: A gallery C++ of cache effects
author: Gabriel Godefroy
---

This repository is strongly inspired by:

 * [“Gallery of Processor Cache Effects“, by Igor Ostrovsky](http://igoro.com/archive/gallery-of-processor-cache-effects/)
 * [“Want fast C++? Know your hardware!“, by Timur Doumler](https://www.youtube.com/watch?v=BP6NxVxDQIs)

## On memory alignement  (padding)

In C++, a variable can not be smaller that the size of a `char` 

```cpp
{{src/m_alignement.cpp}}
```

```
{{build/m_alignement.txt}}
```

TODO m_alignement.svg


## Impact of cache lines

```cpp
constexpr std::size_t nb_elem = 513 * 1024 * 1024;
std::vector<char> vec_char(nb_elem);
for (std::size_t i = 0; i < 1024 * 1024; i++)
    vec[i * delta] += 1;
```


![The impact of cache lines on ](m_cache_lines.png)
