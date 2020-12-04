namespace cache
{
    /*! \brief Prevent instruction re-ordering 
     *  \see https://stackoverflow.com/questions/37786547/enforcing-statement-order-in-c 
     */
    template <class T>
    __attribute__((always_inline)) inline void DoNotOptimize(const T &value)
    {
        asm volatile(""
                     : "+m"(const_cast<T &>(value)));
    }
} // namespace cache