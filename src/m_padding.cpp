#include <iostream>
#include <typeinfo>
#include <map>
#include <string>

#include "f_show_size_alignment.hpp" //helper function

struct Svoid  { };
struct Smeth  { bool mymethod(){return true;}; static void static_meth(){return;} };
struct S_d  { double b; };
struct S_b  { char b; };
struct S_dcc  { double b; char a; char c; };
struct S_cdc  { char a; double b; char c; };
struct S_c1c  { char b1[1]; char b; };
struct S_c8c  { char b8[8]; char b; };
struct S_c9c  { char b9[9]; char b; };

int main()
{
    std::cout << std::string(50,'-') << std::endl;
    cache::show_table_header();
    cache::show_sizes_and_alignments<Smeth, Svoid, Svoid[2],S_d, S_b, S_cdc, S_dcc, S_c1c, S_c8c, S_c9c>();    
    std::cout << std::string(50,'-')<< std::endl;
    return 0;
}
