#include "bitops_traits.inl"

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

#include "clz.inl"

namespace
{
    template <bool cpu_has_lzcnt_support = false, typename T>
    __always_inline int __clz(T value) noexcept
    {
        return _clz(value, std::bool_constant<cpu_has_lzcnt_support>());
    }
}

template <typename T>
__always_inline int clz(T value) noexcept
{
    return __clz<false,T>(value);
}

#include "popcnt.inl"

namespace
{
    template <bool cpu_has_popcnt_support = false, typename T>
    __always_inline int __popcount(T value) noexcept
    {
        return _popcnt(value, std::bool_constant<cpu_has_popcnt_support>());
    }
}

template <typename T>
__always_inline int popcnt(T value) noexcept
{
    return __popcount<false,T>(value);
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
