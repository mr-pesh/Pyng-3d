#pragma intrinsic(_BitScanReverse)

__forceinline int __cpu_has_lzcnt_support() noexcept
{
    int CPUInfo[4];
    __cpuid(CPUInfo, 0x80000001);
    return CPUInfo[2] & 0x000020;
}

template <typename T, std::enable_if_t<sizeof(T) <= sizeof(unsigned short), int> = 0>
__forceinline unsigned short _clz(T value, std::true_type) noexcept
{
    return __lzcnt16(static_cast<unsigned short>(value)) - (sizeof(unsigned short) - sizeof(T)) * 8;
}

template <typename T, std::enable_if_t<sizeof(T) <= sizeof(unsigned short), int> = 0>
__forceinline unsigned short _clz(T value, std::false_type) noexcept
{
    unsigned long index;
    unsigned char notZero = _BitScanReverse(&index, static_cast<unsigned long>(value));
    return notZero ? (((sizeof(unsigned long) * 8) - 1) - static_cast<unsigned short>(index) - (sizeof(unsigned long) - sizeof(T)) * 8) : sizeof(T) * 8;
}

template <typename T, std::enable_if_t<sizeof(T) == sizeof(unsigned int), int> = 0>
__forceinline unsigned int _clz(T value, std::true_type) noexcept
{
    return __lzcnt(static_cast<unsigned int>(value));
}

template <typename T, std::enable_if_t<sizeof(T) == sizeof(unsigned long), int> = 0>
__forceinline unsigned int _clz(T value, std::false_type) noexcept
{
    unsigned long index;
    unsigned char notZero = _BitScanReverse(&index, static_cast<unsigned long>(value));
    return notZero ? (((sizeof(T) * 8) - 1) - static_cast<unsigned int>(index)) : sizeof(T) * 8;
}

#if defined(_M_AMD64) || defined(_M_ARM)

template <typename T, std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline unsigned __int64 _clz(T value, std::true_type) noexcept
{
    return __lzcnt64(static_cast<unsigned __int64>(value));
}

#pragma intrinsic(_BitScanReverse64)

template <typename T, std::enable_if_t<sizeof(T) == sizeof(__int64), int> = 0>
__forceinline unsigned __int64 _clz(T value, std::false_type) noexcept
{
    unsigned long index;
    unsigned char notZero = _BitScanReverse64(&index, static_cast<unsigned __int64>(value));
    return notZero ? (((sizeof(T) * 8) - 1) - static_cast<unsigned __int64>(index)) : sizeof(T) * 8;
}

#endif
