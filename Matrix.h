#pragma once

#include "private/Matrix_base.h"

#ifdef __GL_MATH_LIBRARY

template <typename T, int rows, int columns>
using Matrix = glm::mat<columns, rows, T, glm::defaultp>;

#else

template <typename T, int rows, int columns>
using Matrix = Matrix_Base<T, rows, columns>;

#endif