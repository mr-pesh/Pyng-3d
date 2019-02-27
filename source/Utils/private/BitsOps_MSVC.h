#pragma once

#include <intrin.h>

# pragma intrinsic(_bittest)
template <typename T, typename Size,
          std::enable_if_t<sizeof(T) <= sizeof(__int32), int> = 0>
__forceinline bool bittest(T const *array, Size bit) noexcept
{
    return _bittest(static_cast<long const *>(array), static_cast<long>(bit));
}

# pragma intrinsic(_bittestandset)
template <typename T, typename Size,
          std::enable_if_t<sizeof(T) <= sizeof(__int32), int> = 0>
__forceinline bool bittestandset(T *array, Size bit) noexcept
{
    return _bittestandset(static_cast<long *>(array), static_cast<long>(bit));
}

# pragma intrinsic(_bittestandreset)
template <typename T, typename Size,
          std::enable_if_t<sizeof(T) <= sizeof(__int32), int> = 0>
__forceinline bool bittestandreset(T *array, Size bit) noexcept
{
    return _bittestandreset(static_cast<long *>(array), static_cast<long>(bit));
}

# pragma intrinsic(_bittestandcomplement)
template <typename T, typename Size,
          std::enable_if_t<sizeof(T) <= sizeof(__int32), int> = 0>
__forceinline bool bittestandchange(T *array, Size bit) noexcept
{
    return _bittestandcomplement(static_cast<long *>(array), static_cast<long>(bit));
}

#ifdef _M_AMD64

# pragma intrinsic(_bittest64)
template <typename T, typename Size,
          std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline bool bittest(T const *array, Size bit) noexcept
{
    return _bittest64(static_cast<__int64 const *>(array), static_cast<__int64>(bit));
}

# pragma intrinsic(_bittestandset64)
template <typename T, typename Size,
          std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline bool bittestandset(T *array, Size bit) noexcept
{
    return _bittestandset64(static_cast<__int64 *>(array), static_cast<__int64>(bit));
}

# pragma intrinsic(_bittestandreset64)
template <typename T, typename Size,
          std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline bool bittestandreset(T *array, Size bit) noexcept
{
    return _bittestandreset64(static_cast<__int64 *>(array), static_cast<__int64>(bit));
}

# pragma intrinsic(_bittestandcomplement64)
template <typename T, typename Size,
          std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline bool bittestandchange(T *array, Size bit) noexcept
{
    return _bittestandcomplement64(static_cast<__int64 *>(array), static_cast<__int64>(bit));
}

#endif // _M_AMD64

template <typename T, typename Size>
__forceinline bool getBit(volatile T *value, Size index) noexcept
{
    return bittest(value, index);
}

template <typename T, typename Size>
__forceinline void setBit(volatile T *value, Size index) noexcept
{
    bittestandset(value, index);
}

template <typename T, typename Size>
__forceinline void clearBit(volatile T *value, Size index) noexcept
{
    bittestandreset(value, index);
}

template <typename T, typename Size>
__forceinline void changeBit(volatile T *value, Size index) noexcept
{
    bittestandchange(value, index);
}

# pragma intrinsic(__popcnt16)
template <typename T, std::enable_if_t<sizeof(T) <= sizeof(__int16), int> = 0>
__forceinline unsigned __int16 popcount(T value)
{
    return __popcnt16(static_cast<unsigned __int16>(value));
}

# pragma intrinsic(__popcnt)
template <typename T, std::enable_if_t<sizeof(T) == sizeof(__int32), int> = 0>
__forceinline unsigned __int32 popcount(T value)
{
    return __popcnt(static_cast<unsigned __int32>(value));
}

#ifdef _M_AMD64

# pragma intrinsic(__popcnt64)
template <typename T,
          std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline unsigned __int64 popcount(T value)
{
    return __popcnt64(static_cast<unsigned __int64>(value));
}

#endif // _M_AMD64
