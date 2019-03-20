#pragma once

#include <type_traits>

#ifndef _MSC_VER

namespace std
{
    template<class T, class... Types>
    inline constexpr bool _Is_any_of_v = disjunction_v<is_same<T, Types>...>;
}

#endif // _MSC_VER
