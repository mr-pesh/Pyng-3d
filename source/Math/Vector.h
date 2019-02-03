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
    template <class V>
    constexpr auto begin(const V &vector) noexcept
    {
        if constexpr (std::is_same_v<std::remove_reference_t<V>, XMVECTOR>) {
            return reinterpret_cast<const float*>(&vector);
        }
        else {
            return reinterpret_cast<const decltype(vector.x)*>(&vector);
        }
    }

    template <class V>
    constexpr auto begin(V &&vector) noexcept
    {
        if constexpr (std::is_same_v<std::remove_reference_t<V>, XMVECTOR>) {
            return reinterpret_cast<float*>(&vector);
        }
        else {
            return reinterpret_cast<decltype(vector.x)*>(&vector);
        }
    }

    template <class V>
    constexpr auto end(const V &vector) noexcept
    {
        if constexpr (std::is_same_v<std::remove_reference_t<V>, XMVECTOR>) {
            return reinterpret_cast<const float*>(&vector + 1);
        }
        else {
            return reinterpret_cast<const decltype(vector.x)*>(&vector + 1);
        }
    }

    template <class V>
    constexpr auto end(V &&vector) noexcept
    {
        if constexpr (std::is_same_v<std::remove_reference_t<V>, XMVECTOR>) {
            return reinterpret_cast<float*>(&vector + 1);
        }
        else {
            return reinterpret_cast<decltype(vector.x)*>(&vector + 1);
        }
    }
}

template <class T, int length>
using Vector = Vector_Helper_T <T, length>;

#else

template <typename T, int length>
using Vector = Matrix_Base<T, 1, length>;

#endif
