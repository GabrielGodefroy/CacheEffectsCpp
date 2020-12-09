---
title: Memory alignement and padding
---

For a CPU to work efficiently, there are restrictions on the addresses where objects of types are located in memory (_alignment_). In order to respect these alignements, the compiler sometimes needs to insterts extra bytes (_padding_) between the the members of user_defined types. This impact memory consumption...

Computer stores information as bit (i.e., 0 or 1). Bit a not really used alone, but are packed by 8 to form bytes. A 64 bit-processor manipulates bytes 8 by 8. 

## Memory alignement

In C++, a variable can not be smaller that the size of a word, i.e., of a `char`. A `bool` cannot be represent by a single bit. For a CPU to work efficiently, there are further restrictions on the addresses where objects of types are located in memory. The code below shows the sizes and the alignement for various standard types.

```cpp
{{src/m_alignement.cpp}}
```

```
{{build/m_alignement.txt}}
```
On my architecture, `char` and `bool` are stored using 1 byte, and can be aligned everywhere. A `double` uses  `8` bytes, and needs to be aligned on a 8th byte, as shown below 

TODO m_alignement.svg

## Padding 

Alignement has implication when packing object into user-defined types.


```cpp
{{src/m_padding.cpp}}
```

```
{{build/m_padding.txt}}
```

We can observed that storing an empty type takes 1 byte. Storing a built-in type has no space overhead. However, when mixing types when can observe that the size of a user-defined type is not necessarily the size of the sum of the contained types. For example, `S_cdc` and `S_dcc` both contain 1 `double` and 2 `char`.

 * `size(S_cdc)==24` and
 * `size(S_dcc)==16` 
 * while `size(double)+2*size(char)==8+2*1==10`).

 This is due to the alignement of `double`, which is 8. In the case of `S_cdc`, after the first char, 7 unused bytes while be added to respect the padding of the double. Same thing after the second char, to respect the padding of the object itself:

 ||c**eeeeeee**||dddddddd||c**eeeeeeee**|| (|| are 8-bytes separators and *e* and empty byte added for padding)

 In the case of `S_dcc`, on 6 empty bytes are needed, saving 8 bytes:

 ||dddddddd||cc**eeeeeee**|




## To remember

 * the size of user defined type is NOT the necessaily equal to the sum of the sizes of its components. 
 * by re-arranging the order in which members are defined, we can reduce the amount of memory consumed by one object.
 * a rule of thumb to reduce object size is to define large members first, and to leave small ones at the end of the class.


 | --------------------------------- | --------------------------------- | --------------------------------- |
|:--|:--:|--:|
|  | [Main page](index.html) | [Next page](cache_lines.html) |
