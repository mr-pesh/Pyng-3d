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

#include "popcnt.inl"

template <typename T>
__always_inline int popcount(T value) noexcept
{
    return popcnt(value);
}

#include "bittest.inl"

template <typename T, typename Size>
__always_inline bool getBit(T const& value, Size index) noexcept
{
    return bittest(&value, index);
}

#include "bittestandset.inl"

template <typename T, typename Size>
__always_inline void setBit(T& value, Size index) noexcept
{
    bittestandset(&value, index);
}

#include "bittestandreset.inl"

template <typename T, typename Size>
__always_inline void clearBit(T& value, Size index) noexcept
{
    bittestandreset(&value, index);
}

#include "bittestandchange.inl"

template <typename T, typename Size>
__always_inline void flipBit(T& value, Size index) noexcept
{
    bittestandchange(&value, index);
}