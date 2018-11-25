#pragma once

#include "private/Matrix_base.h"

#ifdef __GL_MATH_LIBRARY

#include <glm/matrix.hpp>

template <typename T, int length, glm::qualifier precision = glm::defaultp>
using Vector = glm::vec<length, T, precision>;

#else

template <typename T, int length>
using Vector = Matrix_Base<T, 1, length>;

#endif
