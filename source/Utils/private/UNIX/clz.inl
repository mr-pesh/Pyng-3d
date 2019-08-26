template <typename T>
__always_inline int _clz(T value) noexcept
{
    using namespace __bitops_traits;
    return ({
         __builtin_choose_expr(sizeof(T) < sizeof(unsigned int),
             __builtin_clz(static_cast<unsigned int>(value)) - ((sizeof(unsigned int) - sizeof(T)) * 8),
         __builtin_choose_expr(_Is_any_of_v<T, int, unsigned int>,
             __builtin_clz(static_cast<unsigned int>(value)),
         __builtin_choose_expr(_Is_any_of_v<T, long, unsigned long>,
             __builtin_clzl(static_cast<unsigned long>(value)),
         __builtin_choose_expr(_Is_any_of_v<T, long long, unsigned long long>,
             __builtin_clzll(static_cast<unsigned long long>(value)),
         (void)0))));
    });
}
