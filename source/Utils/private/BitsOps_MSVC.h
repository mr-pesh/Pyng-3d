#pragma once

#include <intrin.h>

# pragma intrinsic(__popcnt16, __popcnt)
#ifdef _M_AMD64
# pragma intrinsic(__popcnt64)
#endif
template <typename T>
__forceinline auto popcount(T value) noexcept
{
    if constexpr (sizeof(T) == sizeof(unsigned short)) {
        return __popcnt16((unsigned short)value);
    }
    else if (sizeof(T) == sizeof(unsigned int)) {
        return __popcnt((unsigned int)value);
    }
#ifdef _M_AMD64
    else if (sizeof(T) == sizeof(unsigned __int64)) {
        return __popcnt64((unsigned __int64)value);
    }
#endif
}

# pragma intrinsic(_bittest)
#ifdef _M_AMD64
# pragma intrinsic(_bittest64)
#endif
template <typename T, typename Size>
__forceinline bool bittest(T const *array, Size bit) noexcept
{
    if constexpr (sizeof(T) < sizeof(__int64)) {
        return _bittest((long const *)array, (long)bit);
    }
#ifdef _M_AMD64
    else if (sizeof(T) == sizeof(__int64)) {
        return _bittest64((__int64 const *)array, (__int64)bit);
    }
#endif
}

# pragma intrinsic(_bittestandset)
#ifdef _M_AMD64
# pragma intrinsic(_bittestandset64)
#endif
template <typename T, typename Size>
__forceinline bool bittestandset(T *array, Size bit) noexcept
{
    if constexpr (sizeof(T) < sizeof(__int64)) {
        return _bittestandset((long *)array, (long)bit);
    }
#ifdef _M_AMD64
    else if (sizeof(T) == sizeof(__int64)) {
        return _bittestandset64((__int64 *)array, (__int64)bit);
    }
#endif
}

# pragma intrinsic(_bittestandreset)
#ifdef _M_AMD64
# pragma intrinsic(_bittestandreset64)
#endif
template <typename T, typename Size>
__forceinline bool bittestandreset(T *array, Size bit) noexcept
{
    if constexpr (sizeof(T) < sizeof(__int64)) {
        return _bittestandreset((long *)array, (long)bit);
    }
#ifdef _M_AMD64
    else if (sizeof(T) == sizeof(__int64)) {
        return _bittestandreset64((__int64 *)array, (__int64)bit);
    }
#endif
}

# pragma intrinsic(_bittestandcomplement)
#ifdef _M_AMD64
# pragma intrinsic(_bittestandcomplement64)
#endif
template <typename T, typename Size>
__forceinline bool bittestandchange(T *array, Size bit) noexcept
{
    if constexpr (sizeof(T) < sizeof(__int64)) {
        return _bittestandcomplement((long *)array, (long)bit);
    }
#ifdef _M_AMD64
    else if (sizeof(T) == sizeof(__int64)) {
        return _bittestandcomplement64((__int64 *)array, (__int64)bit);
    }
#endif
}

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
