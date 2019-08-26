#include <cpuid.h>

__always_inline int __cpu_has_popcnt_support() noexcept
{
    int CPUInfo[4];
    __cpuid(1, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    return CPUInfo[2] & 0x800000;
}

template <typename T>
__always_inline int _popcnt(T value, std::false_type) noexcept
{
    using namespace __bitops_traits;
    return ({
         __builtin_choose_expr(_Is_any_of_v<T, int, unsigned int> || sizeof(T) < sizeof(unsigned int),
             __builtin_popcount(static_cast<unsigned int>(value)),
         __builtin_choose_expr(_Is_any_of_v<T, long, unsigned long>,
             __builtin_popcountl(static_cast<unsigned long>(value)),
         __builtin_choose_expr(_Is_any_of_v<T, long long, unsigned long long>,
             __builtin_popcountll(static_cast<unsigned long long>(value)),
         (void)0)));
    });
}
