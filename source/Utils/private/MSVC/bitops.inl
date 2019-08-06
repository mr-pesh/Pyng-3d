#include <intrin.h>

#include "popcnt.inl"

template <typename T>
__forceinline int popcount(T value) noexcept
{
    return static_cast<int>(popcnt(value));
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
