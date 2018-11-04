#pragma once

#include "private/Matrix_base.h"

#ifdef __GL_MATH_LIBRARY

#include <glm/matrix.hpp>

template <typename T, int rows, int columns,
           glm::qualifier precision = glm::defaultp>
using Matrix = glm::mat<columns, rows, T, precision>;

#else

template <typename T, int rows, int columns>
using Matrix = Matrix_Base<T, rows, columns>;

#endif
