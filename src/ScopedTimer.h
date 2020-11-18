#pragma once

#include <chrono>

namespace cache
{

    /*! \brief Helps timing scopes
    * Modified from C++ High Performance by V. Sehr & B. Andrist 
    */
    class ScopedTimer
    {
    public:
        using ClockType = std::chrono::steady_clock;
        ScopedTimer(const char *message = nullptr);
        double elapsed_second() const;
        double elapsed_ms() const;

        void print() const;
        ~ScopedTimer();

    private:
        const char *message{};
        const ClockType::time_point start{};

        ScopedTimer(const ScopedTimer &) = delete;
        ScopedTimer &operator=(const ScopedTimer &) = delete;
        ScopedTimer(ScopedTimer &&) = delete;
        ScopedTimer &&operator=(const ScopedTimer &&) = delete;
    };

    ScopedTimer::ScopedTimer(const char *message)
        : message{message},
          start{ClockType::now()}
    {
    }

    double ScopedTimer::elapsed_second() const
    {
        auto now = ClockType::now();
        std::chrono::duration<double> duration = (now - start);
        return duration.count();
    }

    double ScopedTimer::elapsed_ms() const
    {
        return elapsed_second() * 1000.;
    }

    void ScopedTimer::print() const
    {
        std::cout << message << "\t" << elapsed_ms() << " (ms)" << std::endl;
    }

    ScopedTimer::~ScopedTimer()
    {
        if (message != nullptr)
            print();
    }

} // namespace cache