#pragma intrinsic(_bittestandset)
template <typename T, typename Size,
    std::enable_if_t<sizeof(T) <= sizeof(long), int> = 0>
__forceinline unsigned char bittestandset(T* value, Size index) noexcept
{
    return _bittestandset(static_cast<long*>(value), static_cast<long>(index));
}

#ifdef _M_AMD64

#pragma intrinsic(_bittestandset64)
template <typename T, typename Size,
    std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline unsigned char bittestandset(T* value, Size bit) noexcept
{
    return _bittestandset64(static_cast<__int64*>(value), static_cast<__int64>(index));
}

#endif
