#include <typeinfo>
#include <map>
#include <string>
#include <iostream>


namespace cache {


const std::map<std::string, std::string> type_name = {
    {typeid(double).name(), "double"},
    {typeid(short).name(), "short"},
    {typeid(float).name(), "float"},
    {typeid(int).name(), "int"},
    {typeid(char).name(), "char"},
    {typeid(bool).name(), "bool"}};

template <typename T>
std::string get_typename() {
    const std::string key{typeid(T).name()};
    auto it = type_name.find(key);
    if(it!=type_name.end()){
        return it->second;
    }
    return key;
} 

const char* sep = "\t| ";

/*! \brief Display the size and the alignement of a given type */
template <typename T>
void show_size_and_alignment()
{
    const int nb_white_space = std::max<int>(0 ,8-get_typename<T>().size());
    const std::string whitespaces(nb_white_space    , ' ');
    std::cout << "  "<< get_typename<T>() << whitespaces << sep  <<sizeof(T) << " \t" <<sep  << alignof(T) << std::endl;
}

template<typename Arg, typename... Args>  
void show_sizes_and_alignments(){
    show_size_and_alignment<Arg>();
    (show_sizes_and_alignments<Args>(),...);
}

void show_table_header()
{
    std::cout << "\nTYPE\t"  << sep << "sizeof"  << sep << "alignof" << std::endl;
}

}