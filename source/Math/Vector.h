#pragma once

#include "private/Matrix_base.h"

#ifdef __GL_MATH_LIBRARY

#include <glm/matrix.hpp>

template <typename T, int length, glm::qualifier precision = glm::defaultp>
using Vector = glm::vec<length, T, precision>;

#elif defined(__DX_MATH_LIBRARY)

#include "private/DXMapper.h"

namespace std
{
    template <class T, typename value_type = decltype(std::declval<T>().x)>
    constexpr const value_type *begin(const T& dx_value)
    {
        return reinterpret_cast<const value_type*>(&dx_value);
    }

    template <class T, typename value_type = decltype(std::declval<T>().x)>
    constexpr const value_type *end(const T& dx_value)
    {
        return reinterpret_cast<const value_type*>(&dx_value + 1);
    }
}

template <class T, int length>
using Vector = Vector_Helper_T <T, length>;

#else

template <typename T, int length>
using Vector = Matrix_Base<T, 1, length>;

#endif
