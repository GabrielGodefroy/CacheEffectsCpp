#include <iostream>
#include <typeinfo>
#include <bitset>
#include <memory>
#include <map>
#include <string>

struct S_b
{
    bool a;
};

struct S_bbbb
{
    bool a;
    bool b;
    bool c;
    bool d;
};
struct S_bits
{
    std::bitset<64> b;
};


struct S_barr
{
    bool b[64];
};

struct S_bdb
{
    bool a;
    double b;
    bool c;
};
void header();
template <typename T>
void show_size_and_alignment();

int main()
{
    header();
    show_size_and_alignment<bool>();
    show_size_and_alignment<char>();
    show_size_and_alignment<int>();
    show_size_and_alignment<float>();
    show_size_and_alignment<double>();

    show_size_and_alignment<S_b>();
    show_size_and_alignment<S_bbbb>();
    show_size_and_alignment<S_bits>();
    show_size_and_alignment<S_barr>();
    show_size_and_alignment<S_bdb>();

    return 0;
}

void header()
{
    std::cout << "TYPE"
              << "\t"
              << "SIZE"
              << "\t"
              << "ALIGN" << std::endl;
}

const std::map<std::string, std::string> type_name = {
    {typeid(double).name(), "double"},
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

template <typename T>
void show_size_and_alignment()
{
    std::cout << get_typename<T>() << "\t" << sizeof(T) << "\t" << alignof(T) << std::endl;
}
