#pragma once

/**
 * @class Vector
 *
 * Generalized alias to one of
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#gabe65c061834f61b4f7cb6037b19006a4">vec2</a>,
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga9c3019b13faf179e4ad3626ea66df334">vec3</a>,
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#gac215a35481a6597d1bf622a382e9d6e2">vec4</a>,
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga6f9269106d91b2d2b91bcf27cd5f5560">ivec2</a>,
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#gad0d784d8eee201aca362484d2daee46c">ivec3</a>,
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga5abb4603dae0ce58c595e66d9123d812">ivec4</a>,
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga2f6d9ec3ae14813ade37d6aee3715fdb">uvec2</a>,
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga3d3e55874babd4bf93baa7bbc83ae418">uvec3</a>,
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#gaa57e96bb337867329d5f43bcc27c1095">uvec4</a> (OpenGL)
 * or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmint2">XMINT2</a>,
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmint3">XMINT3</a>,
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmint4">XMINT4</a>,
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmuint2">XMUINT2</a>,
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmuint3">XMUINT3</a>,
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmuint4">XMUINT4</a>,
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmfloat2">XMFLOAT2</a>,
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmfloat3">XMFLOAT3</a>,
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmfloat4">XMFLOAT4</a> (DirectX)
 * depending on template parameters and platform configuration.
 *
 * @remark It's not recommended to reference this class directly in your code. Use \ref iVec2, \ref iVec3, \ref iVec4, \ref fVec2, \ref fVec3, \ref fVec4, \ref uVec2, \ref uVec3, \ref uVec4 aliases instead.
 */

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

template <typename T, int length, glm::qualifier precision = glm::mediump>
using Vector = glm::vec<length, T, precision>;

#endif

// General vector typedefs

/**
 * @class iVec2
 *
 * **iVec2** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga6f9269106d91b2d2b91bcf27cd5f5560">glm::ivec2</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmint2">DirectX::XMINT2</a>
 * depending on a platform configuration.
 *
 * \sa Vector
 */
typedef Vector<int, 2> iVec2;
/**
 * @class iVec3
 *
 * **iVec3** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#gad0d784d8eee201aca362484d2daee46c">glm::ivec3</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmint3">DirectX::XMINT3</a>
 * depending on a platform configuration.
 *
 * \sa Vector
 */
typedef Vector<int, 3> iVec3;
/**
 * @class iVec4
 *
 * **iVec4** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga5abb4603dae0ce58c595e66d9123d812">glm::ivec4</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmint4">DirectX::XMINT4</a>
 * depending on a platform configuration.
 *
 * \sa Vector
 */
typedef Vector<int, 4> iVec4;

/**
 * @class fVec2
 *
 * **fVec2** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#gabe65c061834f61b4f7cb6037b19006a4">glm::vec2</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmfloat2">DirectX::XMFLOAT2</a>
 * depending on a platform configuration.
 *
 * \sa Vector
 */
typedef Vector<float, 2> fVec2;
/**
 * @class fVec3
 *
 * **fVec3** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga9c3019b13faf179e4ad3626ea66df334">glm::vec3</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmfloat3">DirectX::XMFLOAT3</a>
 * depending on a platform configuration.
 *
 * \sa Vector
 */
typedef Vector<float, 3> fVec3;
/**
 * @class fVec4
 *
 * **fVec4** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#gac215a35481a6597d1bf622a382e9d6e2">glm::vec4</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmfloat4">DirectX::XMFLOAT4</a>
 * depending on a platform configuration.
 *
 * \sa Vector
 */
typedef Vector<float, 4> fVec4;

/**
 * @class uVec2
 *
 * **uVec2** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga2f6d9ec3ae14813ade37d6aee3715fdb">glm::uvec2</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmuint2">DirectX::XMUINT2</a>
 * depending on a platform configuration.
 *
 * \sa Vector
 */
typedef Vector<uint32_t, 2> uVec2;
/**
 * @class uVec3
 *
 * **uVec3** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga3d3e55874babd4bf93baa7bbc83ae418">glm::uvec3</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmuint3">DirectX::XMUINT3</a>
 * depending on a platform configuration.
 *
 * \sa Vector
 */
typedef Vector<uint32_t, 3> uVec3;
/**
 * @class uVec4
 *
 * **uVec4** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#gaa57e96bb337867329d5f43bcc27c1095">glm::uvec4</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmuint4">DirectX::XMUINT4</a>
 * depending on a platform configuration.
 *
 * \sa Vector
 */
typedef Vector<uint32_t, 4> uVec4;

/**
 * An alias to \ref fVec2
 */
typedef fVec2 Vec2;
/**
 * An alias to \ref fVec3
 */
typedef fVec3 Vec3;
/**
 * An alias to \ref fVec4
 */
typedef fVec4 Vec4;

#ifdef __DX_MATH_LIBRARY

// Since DirectXMath doesn't support double precision SSE types

typedef Vec2 dVec2;
typedef Vec3 dVec3;
typedef Vec4 dVec4;

#else

/**
 * @class dVec2
 *
 * **dVec2** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga8b09c71aaac7da7867ae58377fe219a8">glm::dvec2</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmfloat2">DirectX::XMFLOAT2</a>
 * depending on a platform configuration.
 *
 * @remark Note that <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath">DirectXMath</a> has no support for double-precision floating point vectors, therefore this class is not recommended to use for compatibility reasons.
 *
 * \sa Vector
 */
typedef Vector<double, 2> dVec2;
/**
 * @class dVec3
 *
 * **dVec3** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga5b83ae3d0fdec519c038e4d2cf967cf0">glm::dvec3</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmfloat3">DirectX::XMFLOAT3</a>
 * depending on a platform configuration.
 *
 * @remark Note that <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath">DirectXMath</a> has no support for double-precision floating point vectors, therefore this class is not recommended to use for compatibility reasons.
 *
 * \sa Vector
 */
typedef Vector<double, 3> dVec3;
/**
 * @class dVec4
 *
 * **dVec4** is an alias to
 * <a href="https://glm.g-truc.net/0.9.9/api/a00699.html#ga57debab5d98ce618f7b2a97fe26eb3ac">glm::dvec4</a> or
 * <a href="https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/ns-directxmath-xmfloat4">DirectX::XMFLOAT4</a>
 * depending on a platform configuration.
 *
 * @remark Note that <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath">DirectXMath</a> has no support for double-precision floating point vectors, therefore this class is not recommended to use for compatibility reasons.
 *
 * \sa Vector
 */
typedef Vector<double, 4> dVec4;

#endif

// Win SDK 8.1 style definitions

template <typename T>
using Vector2 = Vector<T, 2>;
template <typename T>
using Vector3 = Vector<T, 3>;
template <typename T>
using Vector4 = Vector<T, 4>;

// Common HLSL-compatible vector typedefs

/**
 * An alias to int
 */
typedef int32_t int1;

/**
 * An alias to \ref iVec2
 */
typedef Vector2<int> int2;
/**
 * An alias to \ref iVec3
 */
typedef Vector3<int> int3;
/**
 * An alias to \ref iVec4
 */
typedef Vector4<int> int4;

/**
 * An alias to unsigned int
 */
typedef uint32_t uint1;

/**
 * An alias to \ref uVec2
 */
typedef Vector2<uint32_t> uint2;
/**
 * An alias to \ref uVec3
 */
typedef Vector3<uint32_t> uint3;
/**
 * An alias to \ref uVec4
 */
typedef Vector4<uint32_t> uint4;

/**
 * An alias to float
 */
typedef float_t float1;

/**
 * An alias to \ref fVec2
 */
typedef Vector2<float_t> float2;
/**
 * An alias to \ref fVec3
 */
typedef Vector3<float_t> float3;
/**
 * An alias to \ref fVec4
 */
typedef Vector4<float_t> float4;
