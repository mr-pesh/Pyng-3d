#pragma once

#ifdef __GL_MATH_LIBRARY

#include <glm/matrix.hpp>

template <typename T, int rows, int columns, glm::qualifier precision = glm::mediump>
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
using Matrix = XMMatrixAdapterT <T, rows, columns>;

// Win SDK 8.1 style definitions

template <typename T>
using Matrix3x3 = Matrix<T, 3, 3>;
template <typename T>
using Matrix3x4 = Matrix<T, 3, 4>;
template <typename T>
using Matrix4x3 = Matrix<T, 4, 3>;
template <typename T>
using Matrix4x4 = Matrix<T, 4, 4>;

// Common HLSL-compatible matrix typedefs

typedef Matrix3x3<int> int3x3;
typedef Matrix3x4<int> int3x4;
typedef Matrix4x3<int> int4x3;
typedef Matrix4x4<int> int4x4;

typedef Matrix3x3<uint> uint3x3;
typedef Matrix3x4<uint> uint3x4;
typedef Matrix4x3<uint> uint4x3;
typedef Matrix4x4<uint> uint4x4;

typedef Matrix3x3<float> float3x3;
typedef Matrix3x4<float> float3x4;
typedef Matrix4x3<float> float4x3;
typedef Matrix4x4<float> float4x4;

#elif defined(__CPP_AMP_ACCELERATION)

#include "private/Matrix_base.h"

template <typename T, int rows, int columns>
using Matrix = Matrix_Base<T, rows, columns>;

#endif

// General matrix typedefs

typedef Matrix<float, 3, 3> Mat3x3;
typedef Matrix<float, 3, 4> Mat3x4;
typedef Matrix<float, 4, 3> Mat4x3;
typedef Matrix<float, 4, 4> Mat4x4;


#ifdef __DX_MATH_LIBRARY

// Since DirectXMath doesn't support double precision SSE types

typedef Mat3x3 dMat3x3;
typedef Mat3x4 dMat3x4;
typedef Mat4x3 dMat4x3;
typedef Mat4x3 dMat4x4;

#else

typedef Matrix<double, 3, 3> dMat3x3;
typedef Matrix<double, 3, 4> dMat3x4;
typedef Matrix<double, 4, 3> dMat4x3;
typedef Matrix<double, 4, 4> dMat4x4;

#endif
