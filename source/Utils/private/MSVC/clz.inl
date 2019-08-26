#pragma intrinsic(_BitScanReverse)

template <typename T, std::enable_if_t<sizeof(T) <= sizeof(long), int> = 0>
__forceinline unsigned char _clz(T value) noexcept
{
    unsigned long index;
    unsigned char notZero = _BitScanReverse(&index, static_cast<unsigned long>(value));
    return 31 - static_cast<unsigned char>(index);
}

#if defined(_M_AMD64) || defined(_M_ARM)

#pragma intrinsic(_BitScanReverse64)

template <typename T, std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline unsigned char _clz(T value) noexcept
{
    unsigned long index;
    unsigned char notZero = _BitScanReverse64(&index, static_cast<unsigned __int64>(value));
    return 63 - static_cast<unsigned char>(index);
}

#endif
