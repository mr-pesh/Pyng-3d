#include "clz.inl"

template <typename T>
__forceinline int clz(T value) noexcept
{
    return static_cast<int>(_clz(value));
}

#include "popcnt.inl"

namespace
{
    template <bool cpu_has_popcnt_support = false, typename T>
    __forceinline int __popcount(T value) noexcept
    {
        return static_cast<int>(_popcnt(value, std::bool_constant<cpu_has_popcnt_support>()));
    }
}

template <typename T>
__forceinline int popcnt(T value) noexcept
{
    return __popcount<false,T>(value);
}

#include "bittest.inl"

template <typename T, typename Size>
__forceinline bool getBit(T const& value, Size index) noexcept
{
    return bittest(&value, index);
}

#include "bittestandset.inl"

template <typename T, typename Size>
__forceinline void setBit(T& value, Size index) noexcept
{
    bittestandset(&value, index);
}

#include "bittestandreset.inl"

template <typename T, typename Size>
__forceinline void clearBit(T& value, Size index) noexcept
{
    bittestandreset(&value, index);
}

#include "bittestandchange.inl"

template <typename T, typename Size>
__forceinline void flipBit(T& value, Size index) noexcept
{
    bittestandchange(&value, index);
}
