#include <type_traits>

namespace __bitops_traits
{
    template<class...> struct disjunction : std::false_type { };
    template<class B1> struct disjunction<B1> : B1 { };
    template<class B1, class... Bn>
    struct disjunction<B1, Bn...>
        : std::conditional_t<bool(B1::value), B1, disjunction<Bn...>>  { };

    template <class T, class ...Types>
    constexpr bool _Is_any_of_v = disjunction<std::is_same<T, Types>...>::value;
}
