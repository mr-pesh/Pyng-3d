#pragma once

#ifdef __GL_MATH_LIBRARY

#include <glm/matrix.hpp>

template <typename T, int length, glm::qualifier precision = glm::mediump>
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

template <typename T, int length>
using Vector = XMVectorAdapterT<T, length>;

// Win SDK 8.1 style definitions

template <typename T>
using Vector2 = Vector<T, 2>;
template <typename T>
using Vector3 = Vector<T, 3>;
template <typename T>
using Vector4 = Vector<T, 4>;

// Common HLSL-compatible vector typedefs

typedef int32_t int1;

typedef Vector2<int> int2;
typedef Vector3<int> int3;
typedef Vector4<int> int4;

typedef uint32_t uint1;

typedef Vector2<uint> uint2;
typedef Vector3<uint> uint3;
typedef Vector4<uint> uint4;

typedef float_t float1;

typedef Vector2<float> float2;
typedef Vector3<float> float3;
typedef Vector4<float> float4;

#elif defined(__CPP_AMP_ACCELERATION)

#include "private/Matrix_base.h"

template <typename T, int length>
using Vector = Matrix_Base<T, 1, length>;

#endif

// General vector typedefs

typedef Vector<int, 2> iVec2;
typedef Vector<int, 3> iVec3;
typedef Vector<int, 4> iVec4;

typedef Vector<float, 2> fVec2;
typedef Vector<float, 3> fVec3;
typedef Vector<float, 4> fVec4;

typedef Vector<uint32_t, 2> uVec2;
typedef Vector<uint32_t, 3> uVec3;
typedef Vector<uint32_t, 4> uVec4;

typedef fVec2 Vec2;
typedef fVec3 Vec3;
typedef fVec4 Vec4;

#ifdef __DX_MATH_LIBRARY

// Since DirectXMath doesn't support double precision SSE types

typedef Vec2 dVec2;
typedef Vec3 dVec3;
typedef Vec4 dVec4;

#else

typedef Vector<double, 2> dVec2;
typedef Vector<double, 3> dVec3;
typedef Vector<double, 4> dVec4;

#endif
