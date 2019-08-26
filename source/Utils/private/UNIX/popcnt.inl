template <typename T>
__always_inline int _popcnt(T value) noexcept
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
