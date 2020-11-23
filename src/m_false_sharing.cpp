#include <thread>
#include <atomic>
#include <iostream>
#include <typeinfo>
#include <vector>
#include "ScopedTimer.h"

constexpr int nb_touch = 500000;

struct AtomicInt
{
    std::atomic<int> atomic;
};

struct alignas(64) AlignedAI
{
    std::atomic<int> atomic;
};

template <typename T>
void work(T &atomic_int)
{
    for (int i = 0; i < nb_touch; ++i)
    {
        atomic_int++;
        asm(""); // https://stackoverflow.com/questions/7083482/
    }
}
void no_sharing()
{
    int plain_int{0};
    cache::ScopedTimer timer("No sharing \t<int>: \t\t\t\t");
    work(plain_int);
}

template <typename T>
void false_sharing(int nb_thread = 1)
{
    const std::string message =
        "False sharing <" +
        std::string(typeid(T).name()) + "> with " +
        std::to_string(nb_thread) + " threads \t";

    std::vector<T> atomics(nb_thread);
    std::vector<std::thread> threads;

    cache::ScopedTimer timer(message.c_str());
    for (auto &atomic : atomics)
        threads.emplace_back([&]() { work(atomic.atomic); });
    for (auto &thread : threads)
        thread.join();
}

int main()
{
    for (int i = 1; i <= 4; ++i)
    {
        false_sharing<AtomicInt>(i);
        false_sharing<AlignedAI>(i);
    }
    no_sharing();
    return 0;
}