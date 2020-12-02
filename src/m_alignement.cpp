#include <iostream>
#include <map>
#include <string>

#include "f_show_size_alignment.hpp" //helper function

int main()
{
    std::cout << std::string(50,'-') << std::endl;
    cache::show_table_header();
    cache::show_sizes_and_alignments<bool, char, short, int, float, double>();
    std::cout << std::string(50,'-')<< std::endl;
    return 0;
}



