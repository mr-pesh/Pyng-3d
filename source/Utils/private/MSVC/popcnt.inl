namespace
{
    __forceinline unsigned __int32 __popcnt_proxy(unsigned __int32 x) noexcept
    {
        x = x - ((x >> 1) & UINT32_C(0x55555555));
        x = (x & UINT32_C(0x33333333)) + ((x >> 2) & UINT32_C(0x33333333));
        x = (x + (x >> 4)) & UINT32_C(0x0F0F0F0F);
        return ((x * UINT32_C(0x01010101)) >> 24);
    }

    __forceinline unsigned __int64 __popcnt_proxy(unsigned __int64 x) noexcept
    {
        x = x - ((x >> 1) & UINT64_C(0x5555555555555555));
        x = (x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333));
        x = (x + (x >> 4)) & UINT64_C(0x0F0F0F0F0F0F0F0F);
        return ((x * UINT64_C(0x0101010101010101)) >> 56);
    }

    __forceinline int __cpu_has_popcnt_support() noexcept
    {
        int CPUInfo[4];
        __cpuid(CPUInfo, 1);
        return CPUInfo[2] & 0x800000;
    }
}

#pragma intrinsic(__popcnt16)
template <typename T,
    std::enable_if_t<sizeof(T) <= sizeof(unsigned __int16), int> = 0>
__forceinline unsigned __int16 popcnt(T value) noexcept
{
    if (__cpu_has_popcnt_support())
        return __popcnt16(static_cast<unsigned __int16>(value));
    else
        return __popcnt_proxy(static_cast<unsigned __int32>(value));
}

#pragma intrinsic(__popcnt)
template <typename T,
    std::enable_if_t<sizeof(T) == sizeof(unsigned __int32), int> = 0>
__forceinline unsigned __int32 popcnt(T value) noexcept
{
    if (__cpu_has_popcnt_support())
        return __popcnt(static_cast<unsigned int>(value));
    else
        return __popcnt_proxy(static_cast<unsigned __int32>(value));
}
#ifdef _M_AMD64
# pragma intrinsic(__popcnt64)
#endif
template <typename T,
    std::enable_if_t<sizeof(T) == sizeof(unsigned __int64), int> = 0>
__forceinline unsigned __int64 popcnt(T value) noexcept
{
    if (__cpu_has_popcnt_support())
#ifndef _M_AMD64
        return __popcnt(static_cast<unsigned __int32>(value >> 32)) + __popcnt(static_cast<unsigned __int32>(value));
#else
        return __popcnt64(static_cast<unsigned __int64>(value));
#endif
    else
        return __popcnt_proxy(static_cast<unsigned __int64>(value));
}
