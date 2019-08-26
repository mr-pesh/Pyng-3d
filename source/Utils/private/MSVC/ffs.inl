#pragma intrinsic(_BitScanForward)

template <typename T, std::enable_if_t<sizeof(T) <= sizeof(long), int> = 0>
__forceinline int _ffs(T value) noexcept
{
    unsigned long index;
    unsigned char notZero = _BitScanForward(&index, static_cast<unsigned long>(value));
    return notZero ? (static_cast<int>(index) + 1) : 0;
}

#if defined(_M_AMD64) || defined(_M_ARM)

#pragma intrinsic(_BitScanForward64)

template <typename T, std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline int _ffs(T value) noexcept
{
    unsigned long index;
    unsigned char notZero = _BitScanForward64(&index, static_cast<unsigned __int64>(value));
    return notZero ? (static_cast<int>(index) + 1) : 0;
}

#endif
