---
title: Memory alignement and padding
author: Gabriel Godefroy
---

For a CPU to work efficiently, there are restrictions on the addresses where objects of types are located in memory (_alignment_). In order to respect these alignements, the compiler sometimes needs to insterts extra bytes (_padding_) between the the members of user_defined types. This impact memory consumption...

## Memory alignement

In C++, a variable can not be smaller that the size of a word, i.e., of a `char` 

```cpp
{{src/m_alignement.cpp}}
```

```
{{build/m_alignement.txt}}
```

TODO m_alignement.svg

## Padding 

```cpp
{{src/m_padding.cpp}}
```

```
{{build/m_padding.txt}}
```