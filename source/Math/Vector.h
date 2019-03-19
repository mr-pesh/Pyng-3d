#pragma once

#if defined(__DX_MATH_LIBRARY)

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

#else

#include "private/GLM_Mapper.h"

template <typename T, int length, glm::qualifier precision = glm::defaultp>
using Vector = glm::vec<length, T, precision>;

#endif

// GLSL-compatible vector typedefs

typedef Vector<int, 2> ivec2;
typedef Vector<int, 3> ivec3;
typedef Vector<int, 4> ivec4;

typedef Vector<float, 2> fvec2;
typedef Vector<float, 3> fvec3;
typedef Vector<float, 4> fvec4;

typedef Vector<uint32_t, 2> uvec2;
typedef Vector<uint32_t, 3> uvec3;
typedef Vector<uint32_t, 4> uvec4;

typedef fvec2 vec2;
typedef fvec3 vec3;
typedef fvec4 vec4;

#ifdef __DX_MATH_LIBRARY

// Since DirectXMath doesn't support double precision SSE types

typedef vec2 dvec2;
typedef vec3 dvec3;
typedef vec4 dvec4;

#else

typedef Vector<double, 2> dvec2;
typedef Vector<double, 3> dvec3;
typedef Vector<double, 4> dvec4;

#endif

// Win SDK 8.1 style definitions

template <typename T>
using Vector2 = Vector<T, 2>;
template <typename T>
using Vector3 = Vector<T, 3>;
template <typename T>
using Vector4 = Vector<T, 4>;

// HLSL-compatible vector typedefs

typedef int32_t int1;

typedef Vector2<int> int2;
typedef Vector3<int> int3;
typedef Vector4<int> int4;

typedef uint32_t uint1;

typedef Vector2<uint32_t> uint2;
typedef Vector3<uint32_t> uint3;
typedef Vector4<uint32_t> uint4;

typedef float_t float1;

typedef Vector2<float_t> float2;
typedef Vector3<float_t> float3;
typedef Vector4<float_t> float4;
