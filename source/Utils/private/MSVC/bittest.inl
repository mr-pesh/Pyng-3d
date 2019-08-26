#pragma intrinsic(_bittest)

template <typename T, typename Size,
    std::enable_if_t<sizeof(T) <= sizeof(long), int> = 0>
__forceinline unsigned char bittest(T const* value, Size index) noexcept
{
    return _bittest(static_cast<long const*>(value), static_cast<long>(index));
}

#if defined(_M_AMD64) || defined(_M_ARM)

#pragma intrinsic(_bittest64)

template <typename T, typename Size,
    std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline unsigned char bittest(T const* value, Size index) noexcept
{
    return _bittest64(static_cast<__int64 const*>(value), static_cast<__int64>(index));
}

#endif
