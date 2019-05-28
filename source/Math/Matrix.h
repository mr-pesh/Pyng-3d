#pragma once

#ifdef __GL_MATH_LIBRARY

#include <glm/matrix.hpp>

template <typename T, int rows, int columns, glm::qualifier precision = glm::mediump>
using Matrix = glm::mat<columns, rows, T, precision>;

#include <glm/gtc/type_ptr.hpp>

#ifdef PYNG_ENABLE_TESTING

namespace std
{
    template <glm::length_t L, typename T, glm::qualifier Q>
    constexpr T *begin(glm::vec<L, T, Q> &vec) noexcept
    {
        return glm::value_ptr(vec);
    }

    template <glm::length_t L, typename T, glm::qualifier Q>
    constexpr T const *begin(const glm::vec<L, T, Q> &vec) noexcept
    {
        return glm::value_ptr(vec);
    }

    template <glm::length_t L, typename T, glm::qualifier Q>
    constexpr T *end(glm::vec<L, T, Q> &vec) noexcept
    {
        return glm::value_ptr(vec) + vec.length();
    }

    template <glm::length_t L, typename T, glm::qualifier Q>
    constexpr T const *end(const glm::vec<L, T, Q> &vec) noexcept
    {
        return glm::value_ptr(vec) + vec.length();
    }
# ifndef GLM_FORCE_PURE
    float_t *begin(glm_vec4 &vec) noexcept
    {
        return reinterpret_cast<float*>(&vec);
    }

    float_t const *begin(const glm_vec4 &vec) noexcept
    {
        return reinterpret_cast<const float*>(&vec);
    }

    float_t *end(glm_vec4 &vec) noexcept
    {
        return reinterpret_cast<float*>(&vec + 1);
    }

    float_t const *end(const glm_vec4 &vec) noexcept
    {
        return reinterpret_cast<const float*>(&vec + 1);
    }
# endif
#endif // PYNG_ENABLE_TESTING
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

typedef Matrix3x3<int32_t> int3x3;
typedef Matrix3x4<int32_t> int3x4;
typedef Matrix4x3<int32_t> int4x3;
typedef Matrix4x4<int32_t> int4x4;

typedef Matrix3x3<float_t> float3x3;
typedef Matrix3x4<float_t> float3x4;
typedef Matrix4x3<float_t> float4x3;
typedef Matrix4x4<float_t> float4x4;

typedef Matrix3x3<uint32_t> uint3x3;
typedef Matrix3x4<uint32_t> uint3x4;
typedef Matrix4x3<uint32_t> uint4x3;
typedef Matrix4x4<uint32_t> uint4x4;

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
