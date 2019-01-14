#pragma once

#include "private/Matrix_base.h"

#ifdef __GL_MATH_LIBRARY

#include <glm/matrix.hpp>

template <typename T, int rows, int columns, glm::qualifier precision = glm::defaultp>
using Matrix = glm::mat<columns, rows, T, precision>;

#include <glm/gtc/type_ptr.hpp>

namespace std
{
    template <typename T>
    constexpr auto begin(const T& glm_type) noexcept
    {
        return glm::value_ptr(glm_type);
    }

    template <typename T>
    constexpr auto end(const T& glm_type) noexcept
    {
        return glm::value_ptr(glm_type) + glm_type.length();
    }
}

#elif defined(__DX_MATH_LIBRARY)

#include "private/DXMapper.h"

template <class T, int rows, int columns>
using Matrix = Matrix_Helper_T <T, rows, columns>;

#else

template <typename T, int rows, int columns>
using Matrix = Matrix_Base<T, rows, columns>;

#endif
