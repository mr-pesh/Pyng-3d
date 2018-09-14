#pragma once

#include "Matrix.h"

#ifdef __DIRECTX_MATH_LIBRARY
# if _MSC_VER < 1800
#  include <xnamath.h>
# else
#  include <DirectXMath.h>
# endif
#endif

#ifndef __DIRECTX_MATH_LIBRARY

template <typename T>
using Matrix3d = Matrix<T, 3, 3>;

#else

template <typename T>
struct Matrix3d : public std::enable_if_t < std::is_same_v<T, float>, DirectX::XMFLOAT3X3 >
{ };

#endif