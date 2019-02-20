#pragma once

#ifndef _MSC_VER
# include "private/BitsOps_UNIX.h"
#else
# include "private/BitsOps_MSVC.h"
#endif

#include <type_traits>

template <typename T, typename Size,
          std::enable_if_t<std::is_integral_v<T>, int> = 0>
constexpr bool getBit(T value, Size index) noexcept
{
    return (value & (1 << index));
}

template <typename T, typename Size,
          std::enable_if_t<std::is_integral_v<T>, int> = 0>
constexpr T setBit(T value, Size index) noexcept
{
    return (value | (1 << index));
}

template <typename T, typename Size,
          std::enable_if_t<std::is_integral_v<T>, int> = 0>
constexpr T clearBit(T value, Size index) noexcept
{
    return (value & ~(1 << index));
}

template <typename T, typename Size,
          std::enable_if_t<std::is_integral_v<T>, int> = 0>
constexpr T changeBit(T value, Size index) noexcept
{
    return getBit(value, index)
            ? clearBit(value, index) : setBit(value,index);
}
