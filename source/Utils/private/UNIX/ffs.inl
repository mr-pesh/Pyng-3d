template <typename T>
__always_inline int _ffs(T value) noexcept
{
    using namespace __bitops_traits;
    return ({
         __builtin_choose_expr(_Is_any_of_v<T, int, unsigned int> || sizeof(T) < sizeof(unsigned int),
             __builtin_ffs(static_cast<unsigned int>(value)),
         __builtin_choose_expr(_Is_any_of_v<T, long, unsigned long>,
             __builtin_ffsl(static_cast<unsigned long>(value)),
         __builtin_choose_expr(_Is_any_of_v<T, long long, unsigned long long>,
             __builtin_ffsll(static_cast<unsigned long long>(value)),
         (void)0)));
    });
}
