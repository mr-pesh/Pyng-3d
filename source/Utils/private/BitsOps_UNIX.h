#pragma once

#include <Utils/Global.h>

#ifdef __GCC_ASM_FLAG_OUTPUTS__
# define CC_SET(c) "\n\t/* output condition code " #c "*/\n"
# define CC_OUT(c) "=@cc" #c
#else
# define CC_SET(c) "\n\tset" #c " %[_cc_" #c "]\n"
# define CC_OUT(c) [_cc_ ## c] "=qm"
#endif

#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 1)
# define BITOP_ADDR(x) "=m" (*(volatile long *) (x))
#else
# define BITOP_ADDR(x) "+m" (*(volatile long *) (x))
#endif

template <typename T>
__always_inline int popcount(T value) noexcept
{
    if constexpr (std::_Is_any_of_v<T, int, unsigned int>
                  || sizeof(T) < sizeof(unsigned int)) {
        return __builtin_popcount(static_cast<unsigned int>(value));
    }
    else if (std::_Is_any_of_v<T, long, unsigned long>) {
        return __builtin_popcountl(static_cast<unsigned long>(value));
    }
    else if (std::_Is_any_of_v<T, long long, unsigned long long>) {
        return __builtin_popcountll(static_cast<unsigned long long>(value));
    }
}

template <typename T, typename Size>
__always_inline bool bittest(volatile const T *value, Size bit) noexcept
{
    bool old;

    asm volatile("bt %2,%1\n\t"
             CC_SET(c)
             : CC_OUT(c) (old)
             : "m" (*value), "Ir" (bit));

    return old;
}

template <typename T, typename Size>
__always_inline bool bittestandset(volatile T *value, Size index) noexcept
{
    bool old;

    asm("bts %2,%1\n\t"
        CC_SET(c)
        : CC_OUT(c) (old), BITOP_ADDR(value)
        : "Ir" (index));

    return old;
}

template <typename T, typename Size>
__always_inline bool bittestandreset(volatile T *value, Size index) noexcept
{
    bool old;

    asm volatile("btr %2,%1\n\t"
             CC_SET(c)
             : CC_OUT(c) (old), BITOP_ADDR(value)
             : "Ir" (index));

    return old;
}

template <typename T, typename Size>
__always_inline bool bittestandchange(volatile T *value, Size index) noexcept
{
    bool old;

    asm volatile("btc %2,%1\n\t"
             CC_SET(c)
             : CC_OUT(c) (old), BITOP_ADDR(value)
             : "Ir" (index) : "memory");

    return old;
}

template <typename T, typename Size>
__always_inline bool getBit(volatile const T *value, Size index) noexcept
{
    return bittest(value, index);
}

template <typename T, typename Size>
__always_inline void setBit(volatile T *value, Size index) noexcept
{
    asm volatile("bts %1,%0" : BITOP_ADDR(value) : "Ir" (index) : "memory");
}

template <typename T, typename Size>
__always_inline void clearBit(volatile T *value, Size index) noexcept
{
    asm volatile("btr %1,%0" : BITOP_ADDR(value) : "Ir" (index) : "memory");
}

template <typename T, typename Size>
__always_inline void changeBit(volatile T *value, Size index) noexcept
{
    asm volatile("btc %1,%0" : BITOP_ADDR(value) : "Ir" (index));
}
