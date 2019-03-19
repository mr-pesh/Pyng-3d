#pragma once

#include <xmmintrin.h>
#include <Utils/TypeTraits.h>

#ifdef __DX_MATH_LIBRARY

namespace DirectX
{
    struct XMINT2;
    struct XMINT3;
    struct XMINT4;

    struct XMUINT2;
    struct XMUINT3;
    struct XMUINT4;

    struct XMFLOAT2;
    struct XMFLOAT3;
    struct XMFLOAT4;

    struct XMMATRIX;

    struct XMFLOAT3X3;
    struct XMFLOAT3X4;
    struct XMFLOAT4X3;
    struct XMFLOAT4X4;
}

#else

#include <glm/fwd.hpp>

#endif

/*-------------------------- Vector traits --------------------------*/

namespace
{
#ifdef __DX_MATH_LIBRARY

    using sint2_t = DirectX::XMINT2;
    using sint3_t = DirectX::XMINT3;
    using sint4_t = DirectX::XMINT4;

    using uint2_t = DirectX::XMUINT2;
    using uint3_t = DirectX::XMUINT3;
    using uint4_t = DirectX::XMUINT4;

    using float2_t = DirectX::XMFLOAT2;
    using float3_t = DirectX::XMFLOAT3;
    using float4_t = DirectX::XMFLOAT4;

#else

    using sint2_t = glm::ivec2;
    using sint3_t = glm::ivec3;
    using sint4_t = glm::ivec4;

    using uint2_t = glm::uvec2;
    using uint3_t = glm::uvec3;
    using uint4_t = glm::uvec4;

    using float2_t = glm::vec2;
    using float3_t = glm::vec3;
    using float4_t = glm::vec4;

#endif

    template <typename T>
    struct _Is_2d_Vector
    {
        static constexpr bool value = std::_Is_any_of_v<std::decay_t<T>, sint2_t, uint2_t, float2_t>;
    };

    template <typename T>
    struct _Is_3d_Vector
    {
        static constexpr bool value = std::_Is_any_of_v<std::decay_t<T>, sint3_t, uint3_t, float3_t>;
    };

    template <typename T>
    struct _Is_4d_Vector
    {
        static constexpr bool value = std::_Is_any_of_v<std::decay_t<T>, sint4_t, uint4_t, float4_t>;
    };

    template <typename T>
    struct _Is_Vector_Type
    {
        static constexpr bool value = std::disjunction_v<_Is_2d_Vector<T>, _Is_3d_Vector<T>, _Is_4d_Vector<T>, std::is_same<T, __m128>>;
    };
}

/**
 * Performs compile-time check wether \p T is a 2D vector.
 */
template<typename T>
inline constexpr bool is2dVector = _Is_2d_Vector<T>::value;

/**
 * Performs compile-time check wether \p T is a 3D vector.
 */
template <typename T>
inline constexpr bool is3dVector = _Is_3d_Vector<T>::value;

/**
 * Performs compile-time check wether \p T is a 4D vector.
 */
template <typename T>
inline constexpr bool is4dVector = _Is_4d_Vector<T>::value;

/**
 * Performs compile-time check wether \p T is 2-, 3- or 4D vector
 */
template <typename T>
inline constexpr bool isVectorType = _Is_Vector_Type<T>::value;

/*-------------------------------------------------------------------*/

/*-------------------------- Matrix traits --------------------------*/

namespace
{
#ifdef __DX_MATH_LIBRARY

    using sint3x3_t = DirectX::XMFLOAT3X3;
    using sint3x4_t = DirectX::XMFLOAT3X4;
    using sint4x3_t = DirectX::XMFLOAT4X3;
    using sint4x4_t = DirectX::XMFLOAT4X4;

    using uint3x3_t = DirectX::XMFLOAT3X3;
    using uint3x4_t = DirectX::XMFLOAT3X4;
    using uint4x3_t = DirectX::XMFLOAT4X3;
    using uint4x4_t = DirectX::XMFLOAT4X4;

    using float3x3_t = DirectX::XMFLOAT3X3;
    using float3x4_t = DirectX::XMFLOAT3X4;
    using float4x3_t = DirectX::XMFLOAT4X3;
    using float4x4_t = DirectX::XMFLOAT4X4;

#else

    using sint3x3_t = glm::mat<3, 3, glm::i32, glm::defaultp>;
    using sint3x4_t = glm::mat<3, 4, glm::i32, glm::defaultp>;
    using sint4x3_t = glm::mat<4, 3, glm::i32, glm::defaultp>;
    using sint4x4_t = glm::mat<4, 4, glm::i32, glm::defaultp>;

    using uint3x3_t = glm::mat<3, 3, glm::u32, glm::defaultp>;
    using uint3x4_t = glm::mat<3, 4, glm::u32, glm::defaultp>;
    using uint4x3_t = glm::mat<4, 3, glm::u32, glm::defaultp>;
    using uint4x4_t = glm::mat<4, 4, glm::u32, glm::defaultp>;

    using float3x3_t = glm::mat<3, 3, glm::f32, glm::defaultp>;
    using float3x4_t = glm::mat<3, 4, glm::f32, glm::defaultp>;
    using float4x3_t = glm::mat<4, 3, glm::f32, glm::defaultp>;
    using float4x4_t = glm::mat<4, 4, glm::f32, glm::defaultp>;

#endif

    template <typename T>
    struct _Is_3x3_Matrix
    {
        static constexpr bool value = std::_Is_any_of_v<std::decay_t<T>, sint3x3_t, uint3x3_t, float3x3_t>;
    };

    template <typename T>
    struct _Is_3x4_Matrix
    {
        static constexpr bool value = std::_Is_any_of_v<std::decay_t<T>, sint3x4_t, uint3x4_t, float3x4_t>;
    };

    template <typename T>
    struct _Is_4x3_Matrix
    {
        static constexpr bool value = std::_Is_any_of_v<std::decay_t<T>, sint4x3_t, uint4x3_t, float4x3_t>;
    };

    template <typename T>
    struct _Is_4x4_Matrix
    {
        static constexpr bool value = std::_Is_any_of_v<std::decay_t<T>, sint4x4_t, uint4x4_t, float4x4_t>;
    };

    template <typename T>
    struct _Is_Matrix_Type
    {
        static constexpr bool value = std::disjunction_v<_Is_3x3_Matrix<T>, _Is_3x4_Matrix<T>, _Is_4x3_Matrix<T>, _Is_4x4_Matrix<T>>
    #ifdef __DX_MATH_LIBRARY
        || std::is_same_v<T, XMMATRIX>
    #endif
        ;
    };
}

/**
 * Performs compile-time check wether \p T is a 3x3 matrix.
 */
template <typename T>
inline constexpr bool is3x3Matrix = _Is_3x3_Matrix<T>::value;

/**
 * Performs compile-time check wether \p T is a 3x4 matrix.
 */
template <typename T>
inline constexpr bool is3x4Matrix = _Is_3x4_Matrix<T>::value;

/**
 * Performs compile-time check wether \p T is a 4x3 matrix.
 */
template <typename T>
inline constexpr bool is4x3Matrix = _Is_4x3_Matrix<T>::value;

/**
 * Performs compile-time check wether \p T is a 4x4 matrix.
 */
template <typename T>
inline constexpr bool is4x4Matrix = _Is_4x4_Matrix<T>::value;

/**
 * Performs compile-time check wether \p T is 3x3, 3x4, 4x3 or 4x4 matrix
 */
template <typename T>
inline constexpr bool isMatrixType = _Is_Matrix_Type<T>::value;

/*-------------------------------------------------------------------*/
