#pragma intrinsic(_bittestandreset)

template <typename T, typename Size,
    std::enable_if_t<sizeof(T) <= sizeof(long), int> = 0>
__forceinline unsigned char bittestandreset(T* value, Size index) noexcept
{
    return _bittestandreset(static_cast<long*>(value), static_cast<long>(index));
}

#ifdef _M_AMD64

#pragma intrinsic(_bittestandreset64)

template <typename T, typename Size,
    std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline unsigned char bittestandreset(T* value, Size index) noexcept
{
    return _bittestandreset64(static_cast<__int64*>(value), static_cast<__int64>(index));
}

#endif
