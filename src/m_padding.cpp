#include <iostream>
#include <typeinfo>
#include <map>
#include <string>

#include "f_show_size_alignment.hpp" //helper function

struct S_dbb  { double b; bool a; bool c; };
struct S_bdb  { bool a; double b; bool c; };
struct S_b1d  { bool b1[1]; double b; };
struct S_b8d  { bool b8[8]; double b; };
struct S_b9d  { bool b9[9]; double b; };

int main()
{
    std::cout << std::string(50,'-') << std::endl;
    cache::show_table_header();
    cache::show_sizes_and_alignments<S_bdb, S_dbb, S_b1d, S_b8d, S_b9d>();    
    std::cout << std::string(50,'-')<< std::endl;
    return 0;
}
