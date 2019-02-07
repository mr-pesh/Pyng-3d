#pragma once

#include <DirectXMath.h>

#define MATCH_TYPE(CompType, Result, Type)                                                    \
    constexpr bool Result = std::is_same_v<std::decay_t<##CompType>, ##Type>;                 \
    static_assert(std::bool_constant<Result>::value, "No matching overload for " __FUNCTION__ )

#define MATCH_TYPE_2(CompType, Result1, Type1, Result2, Type2)                                        \
    using BaseType = std::decay_t<##CompType>;                                                        \
                                                                                                      \
    constexpr bool Result1 = std::is_same_v<BaseType, ##Type1>;                                       \
    constexpr bool Result2 = std::is_same_v<BaseType, ##Type2>;                                       \
                                                                                                      \
    static_assert(std::_Is_any_of_v<BaseType, Type1, Type2>, "No matching overload for " __FUNCTION__ )

#define MATCH_TYPE_3(CompType, Result1, Type1, Result2, Type2, Type3, Result3)                               \
    using BaseType = std::decay_t<##CompType>;                                                               \
                                                                                                             \
    constexpr bool Result1 = std::is_same_v<BaseType, ##Type1>;                                              \
    constexpr bool Result2 = std::is_same_v<BaseType, ##Type2>;                                              \
    constexpr bool Result3 = std::is_same_v<BaseType, ##Type3>;                                              \
                                                                                                             \
    static_assert(std::_Is_any_of_v<BaseType, Type1, Type2, Type3>, "No matching overload for " __FUNCTION__ )

#define IS_2D_VECTOR(T) std::_Is_any_of_v< T, Vector<int32_t,2>, Vector<float_t,2>, Vector<uint32_t,2> >
#define IS_3D_VECTOR(T) std::_Is_any_of_v< T, Vector<int32_t,3>, Vector<float_t,3>, Vector<uint32_t,3> >
#define IS_4D_VECTOR(T) std::_Is_any_of_v< T, Vector<int32_t,4>, Vector<float_t,4>, Vector<uint32_t,4> >

#define IS_VECTOR_TYPE(T) IS_2D_VECTOR(T) || IS_3D_VECTOR(T) || IS_4D_VECTOR(T)

#define IS_3X3_MATRIX(T) std::_Is_any_of_v< T, Matrix<int32_t,3,3>, Matrix<float_t,3,3>, Matrix<uint32_t,3,3> >
#define IS_3X4_MATRIX(T) std::_Is_any_of_v< T, Matrix<int32_t,3,4>, Matrix<float_t,3,4>, Matrix<uint32_t,3,4> >
#define IS_4X3_MATRIX(T) std::_Is_any_of_v< T, Matrix<int32_t,4,3>, Matrix<float_t,4,3>, Matrix<uint32_t,4,3> >
#define IS_4X4_MATRIX(T) std::_Is_any_of_v< T, Matrix<int32_t,4,4>, Matrix<float_t,4,4>, Matrix<uint32_t,4,4> >

#define IS_MATRIX_TYPE(T) IS_3X4_MATRIX(T) || IS_3X3_MATRIX(T) || IS_4X3_MATRIX(T) || IS_4X4_MATRIX(T)


typedef unsigned int uint;

namespace
{
    template <class T, int rows, int columns>
    struct XMMatrixAdapter;

    template <class T>
    struct XMMatrixAdapter<T, 3, 3>
    {
        typedef DirectX::XMFLOAT3X3 Type;
    };

    template <class T>
    struct XMMatrixAdapter<T, 3, 4>
    {
        typedef DirectX::XMFLOAT3X4 Type;
    };

    template <class T>
    struct XMMatrixAdapter<T, 4, 3>
    {
        typedef DirectX::XMFLOAT4X3 Type;
    };

    template <class T>
    struct XMMatrixAdapter<T, 4, 4>
    {
        typedef DirectX::XMFLOAT4X4 Type;
    };
}

template <class T, int rows, int columns>
using XMMatrixAdapterT = typename XMMatrixAdapter<T, rows, columns>::Type;

namespace
{
    using namespace DirectX;

    template <class T, int length>
    struct XMVectorAdapter;

    template <>
    struct XMVectorAdapter<int32_t, 2>
    {
        typedef ::DirectX::XMINT2 Type;

        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2AngleBetweenNormals(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2AngleBetweenNormals(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2AngleBetweenVectors(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2AngleBetweenVectors(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const Type &vec, V2 &&min, V3 &&max) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2ClampLengthV(XMLoadSInt2(&vec), XMLoadSInt2(&min), XMLoadSInt2(&max));
            }
            else if (isXMVector) {
                return XMVector2ClampLengthV(XMLoadSInt2(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
        }

        static __forceinline XMVECTOR ClampLength(const Type &vec, float_t min, float_t max) noexcept
        {
            return XMVector2ClampLength(XMLoadSInt2(&vec), min, max);
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Cross(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Cross(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Dot(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Dot(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool InBounds(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2InBounds(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2InBounds(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Equal(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2EqualInt(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2EqualInt(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Greater(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Greater(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Greater(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2GreaterOrEqual(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2GreaterOrEqual(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Length(const Type &vec) noexcept
        {
            return XMVector2Length(XMLoadSInt2(&vec));
        }

        static __forceinline XMVECTOR LengthSq(const Type &vec) noexcept
        {
            return XMVector2LengthSq(XMLoadSInt2(&vec));
        }

        static __forceinline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector2Less(XMLoadSInt2(&lhs), XMLoadSInt2(&rhs));
        }

        template <class V>
        static __forceinline bool LessOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2LessOrEqual(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2LessOrEqual(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR LinePointDistance(const Type &vec1, const Type &vec2, V &&vec3) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2LinePointDistance(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2), XMLoadSInt2(&vec3));
            }
            else if (isXMVector) {
                return XMVector2LinePointDistance(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2), std::forward<V>(vec3));
            }
        }

        template <class V>
        static __forceinline bool NotEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2NotEqualInt(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2NotEqualInt(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Normalize(const Type &vec) noexcept
        {
            return XMVector2Normalize(XMLoadSInt2(&vec));
        }

        static __forceinline XMVECTOR Orthogonal(const Type &vec) noexcept
        {
            return XMVector2Orthogonal(XMLoadSInt2(&vec));
        }

        static __forceinline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector2ReciprocalLength(XMLoadSInt2(&vec));
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Reflect(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Reflect(XMLoadSInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2RefractV(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2), XMLoadSInt2(&vec3));
            }
            else if (isXMVector) {
                return XMVector2RefractV(XMLoadSInt2(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR Refract(const Type &vec1, V &&vec2, float index) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Refract(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2), index);
            }
            else if (isXMVector) {
                return XMVector2Refract(XMLoadSInt2(&vec1), std::forward<V>(vec2), index);
            }
        }

        template <class M>
        static __forceinline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static __forceinline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), mat);
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct XMVectorAdapter<int32_t, 3>
    {
        typedef ::DirectX::XMINT3 Type;

        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3AngleBetweenNormals(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3AngleBetweenNormals(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3AngleBetweenVectors(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3AngleBetweenVectors(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const Type &vec, V2 &&min, V3 &&max) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3ClampLengthV(XMLoadSInt3(&vec), XMLoadSInt3(&min), XMLoadSInt3(&max));
            }
            else if (isXMVector) {
                return XMVector3ClampLengthV(XMLoadSInt3(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
        }

        static __forceinline XMVECTOR ClampLength(const Type &vec, float min, float max) noexcept
        {
            return XMVector3ClampLength(XMLoadSInt3(&vec), min, max);
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Cross(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Cross(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Dot(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Dot(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool InBounds(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3InBounds(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3InBounds(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Equal(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3EqualInt(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3EqualInt(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Greater(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Greater(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Greater(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3GreaterOrEqual(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3GreaterOrEqual(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Length(const Type &vec) noexcept
        {
            return XMVector3Length(XMLoadSInt3(&vec));
        }

        static __forceinline XMVECTOR LengthSq(const Type &vec) noexcept
        {
            return XMVector3LengthSq(XMLoadSInt3(&vec));
        }

        static __forceinline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector3Less(XMLoadSInt3(&lhs), XMLoadSInt3(&rhs));
        }

        template <class V>
        static __forceinline bool LessOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3LessOrEqual(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3LessOrEqual(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR LinePointDistance(const Type &vec1, const Type &vec2, V &&vec3) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3LinePointDistance(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2), XMLoadSInt3(&vec3));
            }
            else if (isXMVector) {
                return XMVector3LinePointDistance(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2), std::forward<V>(vec3));
            }
        }

        template <class V>
        static __forceinline bool NotEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3NotEqualInt(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3NotEqualInt(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Normalize(const Type &vec) noexcept
        {
            return XMVector3Normalize(XMLoadSInt3(&vec));
        }

        static __forceinline XMVECTOR Orthogonal(const Type &vec) noexcept
        {
            return XMVector3Orthogonal(XMLoadSInt3(&vec));
        }

        static __forceinline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector3ReciprocalLength(XMLoadSInt3(&vec));
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Reflect(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Reflect(XMLoadSInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3RefractV(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2), XMLoadSInt3(&vec3));
            }
            else if (isXMVector) {
                return XMVector3RefractV(XMLoadSInt3(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR Refract(const Type &vec1, V &&vec2, float index) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Refract(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2), index);
            }
            else if (isXMVector) {
                return XMVector3Refract(XMLoadSInt3(&vec1), std::forward<V>(vec2), index);
            }
        }

        template <class M>
        static __forceinline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static __forceinline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), mat);
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct XMVectorAdapter<int32_t, 4>
    {
        typedef ::DirectX::XMINT4 Type;

        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4AngleBetweenNormals(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4AngleBetweenNormals(XMLoadSInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4AngleBetweenVectors(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4AngleBetweenVectors(XMLoadSInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const Type &vec, V2 &&min, V3 &&max) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4ClampLengthV(XMLoadSInt4(&vec), XMLoadSInt4(&min), XMLoadSInt4(&max));
            }
            else if (isXMVector) {
                return XMVector4ClampLengthV(XMLoadSInt4(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
        }

        static __forceinline XMVECTOR ClampLength(const Type &vec, float min, float max) noexcept
        {
            return XMVector4ClampLength(XMLoadSInt4(&vec), min, max);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR CrossProduct(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Cross(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2), XMLoadSInt4(&vec3));
            }
            else if (isXMVector) {
                return XMVector4Cross(XMLoadSInt4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Dot(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4Dot(XMLoadSInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool InBounds(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4InBounds(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4InBounds(XMLoadSInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Equal(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4EqualInt(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4EqualInt(XMLoadSInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Greater(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Greater(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4Greater(XMLoadSInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4GreaterOrEqual(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4GreaterOrEqual(XMLoadSInt4(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Length(const Type &vec) noexcept
        {
            return XMVector4Length(XMLoadSInt4(&vec));
        }

        static __forceinline XMVECTOR LengthSq(const Type &vec) noexcept
        {
            return XMVector4LengthSq(XMLoadSInt4(&vec));
        }

        static __forceinline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector4Less(XMLoadSInt4(&lhs), XMLoadSInt4(&rhs));
        }

        template <class V>
        static __forceinline bool LessOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4LessOrEqual(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4LessOrEqual(XMLoadSInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR LinePointDistance(const Type &vec1, const Type &vec2, V &&vec3) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4LinePointDistance(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2), XMLoadSInt4(&vec3));
            }
            else if (isXMVector) {
                return XMVector4LinePointDistance(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2), std::forward<V>(vec3));
            }
        }

        template <class V>
        static __forceinline bool NotEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4NotEqualInt(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4NotEqualInt(XMLoadSInt4(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Normalize(const Type &vec) noexcept
        {
            return XMVector4Normalize(XMLoadSInt4(&vec));
        }

        static __forceinline XMVECTOR Orthogonal(const Type &vec) noexcept
        {
            return XMVector4Orthogonal(XMLoadSInt4(&vec));
        }

        static __forceinline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector4ReciprocalLength(XMLoadSInt4(&vec));
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Reflect(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4Reflect(XMLoadSInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4RefractV(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2), XMLoadSInt4(&vec3));
            }
            else if (isXMVector) {
                return XMVector4RefractV(XMLoadSInt4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR Refract(const Type &vec1, V &&vec2, float index) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Refract(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2), index);
            }
            else if (isXMVector) {
                return XMVector4Refract(XMLoadSInt4(&vec1), std::forward<V>(vec2), index);
            }
        }

        template <class M>
        static __forceinline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static __forceinline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector4Transform(XMLoadSInt4(&vec), mat);
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector4Transform(XMLoadSInt4(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector4Transform(XMLoadSInt4(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct XMVectorAdapter<float_t, 2>
    {
        typedef ::DirectX::XMFLOAT2 Type;

        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2AngleBetweenNormals(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2AngleBetweenNormals(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2AngleBetweenVectors(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2AngleBetweenVectors(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const Type &vec, V2 &&min, V3 &&max) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2ClampLengthV(XMLoadFloat2(&vec), XMLoadFloat2(&min), XMLoadFloat2(&max));
            }
            else if (isXMVector) {
                return XMVector2ClampLengthV(XMLoadFloat2(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
        }

        static __forceinline XMVECTOR ClampLength(const Type &vec, float min, float max) noexcept
        {
            return XMVector2ClampLength(XMLoadFloat2(&vec), min, max);
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Cross(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Cross(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Dot(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Dot(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool InBounds(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2InBounds(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2InBounds(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Equal(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Equal(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Equal(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Greater(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Greater(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Greater(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2GreaterOrEqual(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2GreaterOrEqual(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Length(const Type &vec) noexcept
        {
            return XMVector2Length(XMLoadFloat2(&vec));
        }

        static __forceinline XMVECTOR LengthSq(const Type &vec) noexcept
        {
            return XMVector2LengthSq(XMLoadFloat2(&vec));
        }

        static __forceinline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector2Less(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs));
        }

        template <class V>
        static __forceinline bool LessOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2LessOrEqual(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2LessOrEqual(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR LinePointDistance(const Type &vec1, const Type &vec2, V &&vec3) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2LinePointDistance(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2), XMLoadFloat2(&vec3));
            }
            else if (isXMVector) {
                return XMVector2LinePointDistance(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2), std::forward<V>(vec3));
            }
        }

        template <class V>
        static __forceinline bool NotEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2NotEqual(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2NotEqual(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Normalize(const Type &vec) noexcept
        {
            return XMVector2Normalize(XMLoadFloat2(&vec));
        }

        static __forceinline XMVECTOR Orthogonal(const Type &vec) noexcept
        {
            return XMVector2Orthogonal(XMLoadFloat2(&vec));
        }

        static __forceinline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector2ReciprocalLength(XMLoadFloat2(&vec));
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Reflect(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Reflect(XMLoadFloat2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2RefractV(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2), XMLoadFloat2(&vec3));
            }
            else if (isXMVector) {
                return XMVector2RefractV(XMLoadFloat2(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR Refract(const Type &vec1, V &&vec2, float index) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Refract(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2), index);
            }
            else if (isXMVector) {
                return XMVector2Refract(XMLoadFloat2(&vec1), std::forward<V>(vec2), index);
            }
        }

        template <class M>
        static __forceinline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static __forceinline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), mat);
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct XMVectorAdapter<float_t, 3>
    {
        typedef ::DirectX::XMFLOAT3 Type;

        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3AngleBetweenNormals(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3AngleBetweenNormals(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3AngleBetweenVectors(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3AngleBetweenVectors(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const Type &vec, V2 &&min, V3 &&max) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);
            
            if constexpr (isSameType) {
                return XMVector3ClampLengthV(XMLoadFloat3(&vec), XMLoadFloat3(&min), XMLoadFloat3(&max));
            }
            else if (isXMVector) {
                return XMVector3ClampLengthV(XMLoadFloat3(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
        }

        static __forceinline XMVECTOR ClampLength(const Type &vec, float min, float max) noexcept
        {
            return XMVector3ClampLength(XMLoadFloat3(&vec), min, max);
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Cross(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Cross(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Dot(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Dot(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool InBounds(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3InBounds(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3InBounds(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Equal(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Equal(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Equal(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Greater(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Greater(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Greater(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3GreaterOrEqual(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3GreaterOrEqual(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Length(const Type &vec) noexcept
        {
            return XMVector3Length(XMLoadFloat3(&vec));
        }

        static __forceinline XMVECTOR LengthSq(const Type &vec) noexcept
        {
            return XMVector3LengthSq(XMLoadFloat3(&vec));
        }

        static __forceinline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector3Less(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs));
        }

        template <class V>
        static __forceinline bool LessOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3LessOrEqual(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3LessOrEqual(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR LinePointDistance(const Type &vec1, const Type &vec2, V &&vec3) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3LinePointDistance(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2), XMLoadFloat3(&vec3));
            }
            else if (isXMVector) {
                return XMVector3LinePointDistance(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2), std::forward<V>(vec3));
            }
        }

        template <class V>
        static __forceinline bool NotEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3NotEqual(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3NotEqual(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Normalize(const Type &vec) noexcept
        {
            return XMVector3Normalize(XMLoadFloat3(&vec));
        }

        static __forceinline XMVECTOR Orthogonal(const Type &vec) noexcept
        {
            return XMVector3Orthogonal(XMLoadFloat3(&vec));
        }

        static __forceinline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector3ReciprocalLength(XMLoadFloat3(&vec));
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Reflect(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Reflect(XMLoadFloat3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3RefractV(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2), XMLoadFloat3(&vec3));
            }
            else if (isXMVector) {
                return XMVector3RefractV(XMLoadFloat3(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR Refract(const Type &vec1, V &&vec2, float index) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Refract(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2), index);
            }
            else if (isXMVector) {
                return XMVector3Refract(XMLoadFloat3(&vec1), std::forward<V>(vec2), index);
            }
        }

        template <class M>
        static __forceinline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static __forceinline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), mat);
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct XMVectorAdapter<float, 4>
    {
        typedef ::DirectX::XMFLOAT4 Type;

        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4AngleBetweenNormals(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4AngleBetweenNormals(XMLoadFloat4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4AngleBetweenVectors(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4AngleBetweenVectors(XMLoadFloat4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const Type &vec, V2 &&min, V3 &&max) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4ClampLengthV(XMLoadFloat4(&vec), XMLoadFloat4(&min), XMLoadFloat4(&max));
            }
            else if (isXMVector) {
                return XMVector4ClampLengthV(XMLoadFloat4(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
        }

        static __forceinline XMVECTOR ClampLength(const Type &vec, float min, float max) noexcept
        {
            return XMVector4ClampLength(XMLoadFloat4(&vec), min, max);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR CrossProduct(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Cross(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2), XMLoadFloat4(&vec3));
            }
            else if (isXMVector) {
                return XMVector4Cross(XMLoadFloat4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Dot(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4Dot(XMLoadFloat4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool InBounds(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4InBounds(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4InBounds(XMLoadFloat4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Equal(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Equal(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4Equal(XMLoadFloat4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Greater(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Greater(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4Greater(XMLoadFloat4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4GreaterOrEqual(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4GreaterOrEqual(XMLoadFloat4(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Length(const Type &vec) noexcept
        {
            return XMVector4Length(XMLoadFloat4(&vec));
        }

        static __forceinline XMVECTOR LengthSq(const Type &vec) noexcept
        {
            return XMVector4LengthSq(XMLoadFloat4(&vec));
        }

        static __forceinline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector4Less(XMLoadFloat4(&lhs), XMLoadFloat4(&rhs));
        }

        template <class V>
        static __forceinline bool LessOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4LessOrEqual(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4LessOrEqual(XMLoadFloat4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR LinePointDistance(const Type &vec1, const Type &vec2, V &&vec3) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4LinePointDistance(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2), XMLoadFloat4(&vec3));
            }
            else if (isXMVector) {
                return XMVector4LinePointDistance(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2), std::forward<V>(vec3));
            }
        }

        template <class V>
        static __forceinline bool NotEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4NotEqual(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4NotEqual(XMLoadFloat4(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Normalize(const Type &vec) noexcept
        {
            return XMVector4Normalize(XMLoadFloat4(&vec));
        }

        static __forceinline XMVECTOR Orthogonal(const Type &vec) noexcept
        {
            return XMVector4Orthogonal(XMLoadFloat4(&vec));
        }

        static __forceinline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector4ReciprocalLength(XMLoadFloat4(&vec));
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Reflect(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4Reflect(XMLoadFloat4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4RefractV(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2), XMLoadFloat4(&vec3));
            }
            else if (isXMVector) {
                return XMVector4RefractV(XMLoadFloat4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR Refract(const Type &vec1, V &&vec2, float index) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Refract(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2), index);
            }
            else if (isXMVector) {
                return XMVector4Refract(XMLoadFloat4(&vec1), std::forward<V>(vec2), index);
            }
        }

        template <class M>
        static __forceinline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static __forceinline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector4Transform(XMLoadFloat4(&vec), mat);
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector4Transform(XMLoadFloat4(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector4Transform(XMLoadFloat4(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct XMVectorAdapter<uint32_t, 2>
    {
        typedef ::DirectX::XMUINT2 Type;

        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2AngleBetweenNormals(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2AngleBetweenNormals(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2AngleBetweenVectors(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2AngleBetweenVectors(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const Type &vec, V2 &&min, V3 &&max) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2ClampLengthV(XMLoadUInt2(&vec), XMLoadUInt2(&min), XMLoadUInt2(&max));
            }
            else if (isXMVector) {
                return XMVector2ClampLengthV(XMLoadUInt2(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
        }

        static __forceinline XMVECTOR ClampLength(const Type &vec, float min, float max) noexcept
        {
            return XMVector2ClampLength(XMLoadUInt2(&vec), min, max);
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Cross(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Cross(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Dot(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Dot(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool InBounds(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2InBounds(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2InBounds(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Equal(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2EqualInt(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2EqualInt(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Greater(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Greater(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Greater(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2GreaterOrEqual(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2GreaterOrEqual(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Length(const Type &vec) noexcept
        {
            return XMVector2Length(XMLoadUInt2(&vec));
        }

        static __forceinline XMVECTOR LengthSq(const Type &vec) noexcept
        {
            return XMVector2LengthSq(XMLoadUInt2(&vec));
        }

        static __forceinline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector2Less(XMLoadUInt2(&lhs), XMLoadUInt2(&rhs));
        }

        template <class V>
        static __forceinline bool LessOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2LessOrEqual(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2LessOrEqual(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR LinePointDistance(const Type &vec1, const Type &vec2, V &&vec3) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2LinePointDistance(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2), XMLoadUInt2(&vec3));
            }
            else if (isXMVector) {
                return XMVector2LinePointDistance(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2), std::forward<V>(vec3));
            }
        }

        template <class V>
        static __forceinline bool NotEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2NotEqualInt(XMLoadUInt2(&vec1), XMLoadUInt2(&vec1));
            }
            else if (isXMVector) {
                return XMVector2NotEqualInt(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Normalize(const Type &vec) noexcept
        {
            return XMVector2Normalize(XMLoadUInt2(&vec));
        }

        static __forceinline XMVECTOR Orthogonal(const Type &vec) noexcept
        {
            return XMVector2Orthogonal(XMLoadUInt2(&vec));
        }

        static __forceinline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector2ReciprocalLength(XMLoadUInt2(&vec));
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Reflect(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
            else if (isXMVector) {
                return XMVector2Reflect(XMLoadUInt2(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2RefractV(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2), XMLoadUInt2(&vec3));
            }
            else if (isXMVector) {
                return XMVector2RefractV(XMLoadUInt2(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR Refract(const Type &vec1, V &&vec2, float index) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector2Refract(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2), index);
            }
            else if (isXMVector) {
                return XMVector2Refract(XMLoadUInt2(&vec1), std::forward<V>(vec2), index);
            }
        }

        template <class M>
        static __forceinline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static __forceinline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), mat);
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct XMVectorAdapter<uint32_t, 3>
    {
        typedef ::DirectX::XMUINT3 Type;

        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3AngleBetweenNormals(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3AngleBetweenNormals(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3AngleBetweenVectors(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3AngleBetweenVectors(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const Type &vec, V2 &&min, V3 &&max) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3ClampLengthV(XMLoadUInt3(&vec), XMLoadUInt3(&min), XMLoadUInt3(&max));
            }
            else if (isXMVector) {
                return XMVector3ClampLengthV(XMLoadUInt3(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
        }

        static __forceinline XMVECTOR ClampLength(const Type &vec, float min, float max) noexcept
        {
            return XMVector3ClampLength(XMLoadUInt3(&vec), min, max);
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Cross(XMLoadUInt3(&vec1), XMLoadUInt3(&vec1));
            }
            else if (isXMVector) {
                return XMVector3Cross(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Dot(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Dot(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool InBounds(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3InBounds(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3InBounds(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Equal(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3EqualInt(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3EqualInt(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Greater(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Greater(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Greater(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3GreaterOrEqual(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3GreaterOrEqual(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Length(const Type &vec) noexcept
        {
            return XMVector3Length(XMLoadUInt3(&vec));
        }

        static __forceinline XMVECTOR LengthSq(const Type &vec) noexcept
        {
            return XMVector3LengthSq(XMLoadUInt3(&vec));
        }

        static __forceinline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector3Less(XMLoadUInt3(&lhs), XMLoadUInt3(&rhs));
        }

        template <class V>
        static __forceinline bool LessOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3LessOrEqual(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3LessOrEqual(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR LinePointDistance(const Type &vec1, const Type &vec2, V &&vec3) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3LinePointDistance(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2), XMLoadUInt3(&vec3));
            }
            else if (isXMVector) {
                return XMVector3LinePointDistance(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2), std::forward<V>(vec3));
            }
        }

        template <class V>
        static __forceinline bool NotEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3NotEqualInt(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3NotEqualInt(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Normalize(const Type &vec) noexcept
        {
            return XMVector3Normalize(XMLoadUInt3(&vec));
        }

        static __forceinline XMVECTOR Orthogonal(const Type &vec) noexcept
        {
            return XMVector3Orthogonal(XMLoadUInt3(&vec));
        }

        static __forceinline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector3ReciprocalLength(XMLoadUInt3(&vec));
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Reflect(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
            else if (isXMVector) {
                return XMVector3Reflect(XMLoadUInt3(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3RefractV(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2), XMLoadUInt3(&vec3));
            }
            else if (isXMVector) {
                return XMVector3RefractV(XMLoadUInt3(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR Refract(const Type &vec1, V &&vec2, float index) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector3Refract(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2), index);
            }
            else if (isXMVector) {
                return XMVector3Refract(XMLoadUInt3(&vec1), std::forward<V>(vec2), index);
            }
        }

        template <class M>
        static __forceinline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static __forceinline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), mat);
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct XMVectorAdapter<uint32_t, 4>
    {
        typedef ::DirectX::XMUINT4 Type;

        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4AngleBetweenNormals(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4AngleBetweenNormals(XMLoadUInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4AngleBetweenVectors(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4AngleBetweenVectors(XMLoadUInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const Type &vec, V2 &&min, V3 &&max) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4ClampLengthV(XMLoadUInt4(&vec), XMLoadUInt4(&min), XMLoadUInt4(&max));
            }
            else if (isXMVector) {
                return XMVector4ClampLengthV(XMLoadUInt4(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
        }

        static __forceinline XMVECTOR ClampLength(const Type &vec, float min, float max) noexcept
        {
            return XMVector4ClampLength(XMLoadUInt4(&vec), min, max);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR CrossProduct(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Cross(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2), XMLoadUInt4(&vec3));
            }
            else if (isXMVector) {
                return XMVector4Cross(XMLoadUInt4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Dot(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4Dot(XMLoadUInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool InBounds(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4InBounds(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4InBounds(XMLoadUInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Equal(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4EqualInt(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4EqualInt(XMLoadUInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool Greater(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Greater(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4Greater(XMLoadUInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4GreaterOrEqual(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4GreaterOrEqual(XMLoadUInt4(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Length(const Type &vec) noexcept
        {
            return XMVector4Length(XMLoadUInt4(&vec));
        }

        static __forceinline XMVECTOR LengthSq(const Type &vec) noexcept
        {
            return XMVector4LengthSq(XMLoadUInt4(&vec));
        }

        static __forceinline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector4Less(XMLoadUInt4(&lhs), XMLoadUInt4(&rhs));
        }

        template <class V>
        static __forceinline bool LessOrEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4LessOrEqual(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4LessOrEqual(XMLoadUInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V>
        static __forceinline XMVECTOR LinePointDistance(const Type &vec1, const Type &vec2, V &&vec3) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4LinePointDistance(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2), XMLoadUInt4(&vec3));
            }
            else if (isXMVector) {
                return XMVector4LinePointDistance(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2), std::forward<V>(vec3));
            }
        }

        template <class V>
        static __forceinline bool NotEqual(const Type &vec1, V &&vec2)
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4NotEqualInt(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4NotEqualInt(XMLoadUInt4(&vec1), std::forward<V>(vec2));
            }
        }

        static __forceinline XMVECTOR Normalize(const Type &vec) noexcept
        {
            return XMVector4Normalize(XMLoadUInt4(&vec));
        }

        static __forceinline XMVECTOR Orthogonal(const Type &vec) noexcept
        {
            return XMVector4Orthogonal(XMLoadUInt4(&vec));
        }

        static __forceinline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector4ReciprocalLength(XMLoadUInt4(&vec));
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const Type &vec1, V &&vec2) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Reflect(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
            else if (isXMVector) {
                return XMVector4Reflect(XMLoadUInt4(&vec1), std::forward<V>(vec2));
            }
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const Type &vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            MATCH_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4RefractV(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2), XMLoadUInt4(&vec3));
            }
            else if (isXMVector) {
                return XMVector4RefractV(XMLoadUInt4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
        }

        template <class V>
        static __forceinline XMVECTOR Refract(const Type &vec1, V &&vec2, float index) noexcept
        {
            MATCH_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isSameType) {
                return XMVector4Refract(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2), index);
            }
            else if (isXMVector) {
                return XMVector4Refract(XMLoadUInt4(&vec1), std::forward<V>(vec2), index);
            }
        }

        template <class M>
        static __forceinline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static __forceinline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector4Transform(XMLoadUInt4(&vec), mat);
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector4Transform(XMLoadUInt4(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static __forceinline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector4Transform(XMLoadUInt4(&vec), XMLoadFloat4x4(&mat));
        }
    };
}

template <class T, int length>
using XMVectorAdapterT = typename XMVectorAdapter<T, length>::Type;

namespace
{
    using namespace DirectX;

    template <class Vector, class Matrix>
    struct TransformMapper;

    template <class Matrix>
    struct TransformMapper<XMINT2, Matrix>
    {
        static XMINT2 Transform(const XMINT2 &v, const Matrix &m)
        {
            XMINT2 result;
            XMStoreSInt2(&result, XMVectorAdapter<int32_t, 2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMINT3, Matrix>
    {
        static XMINT3 Transform(const XMINT3 &v, const Matrix &m)
        {
            XMINT3 result;
            XMStoreSInt3(&result, XMVectorAdapter<int32_t, 3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMINT4, Matrix>
    {
        static XMINT4 Transform(const XMINT4 &v, const Matrix &m)
        {
            XMINT4 result;
            XMStoreSInt4(&result, XMVectorAdapter<int32_t, 4>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMFLOAT2, Matrix>
    {
        static XMFLOAT2 Transform(const XMFLOAT2 &v, const Matrix &m)
        {
            XMFLOAT2 result;
            XMStoreFloat2(&result, XMVectorAdapter<float_t, 2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMFLOAT3, Matrix>
    {
        static XMFLOAT3 Transform(const XMFLOAT3 &v, const Matrix &m)
        {
            XMFLOAT3 result;
            XMStoreFloat3(&result, XMVectorAdapter<float_t, 3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMFLOAT4, Matrix>
    {
        static XMFLOAT4 Transform(const XMFLOAT4 &v, const Matrix &m)
        {
            XMFLOAT4 result;
            XMStoreFloat4(&result, XMVectorAdapter<float_t, 4>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMUINT2, Matrix>
    {
        static XMUINT2 Transform(const XMUINT2 &v, const Matrix &m)
        {
            XMUINT2 result;
            XMStoreUInt2(&result, XMVectorAdapter<uint32_t, 2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMUINT3, Matrix>
    {
        static XMUINT3 Transform(const XMUINT3 &v, const Matrix &m)
        {
            XMUINT3 result;
            XMStoreUInt3(&result, XMVectorAdapter<uint32_t, 3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMUINT4, Matrix>
    {
        static XMUINT4 Transform(const XMUINT4 &v, const Matrix &m)
        {
            XMUINT4 result;
            XMStoreUInt4(&result, XMVectorAdapter<uint32_t, 4>::Transform(v,m));
            return result;
        }
    };
}

namespace
{
    using namespace DirectX;

    template <class V>
    struct Vector_Comparator;

    template <>
    struct Vector_Comparator<XMINT2>
    {
        static __forceinline bool Less(const XMINT2 &v1, const XMINT2 &v2)
        {
            return XMVectorAdapter<int32_t,2>::Less(v1,v2);
        }

        template <class V>
        static __forceinline bool LessOrEqual(const XMINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,2>::LessOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Greater(const XMINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,2>::Greater(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const XMINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,2>::GreaterOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Equal(const XMINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,2>::Equal(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool NotEqual(const XMINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,2>::NotEqual(v1, std::forward<V>(v2));
        }
    };

    template <>
    struct Vector_Comparator<XMINT3>
    {
        static __forceinline bool Less(const XMINT3 &v1, const XMINT3 &v2)
        {
            return XMVectorAdapter<int32_t,3>::Less(v1,v2);
        }

        template <class V>
        static __forceinline bool LessOrEqual(const XMINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,3>::LessOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Greater(const XMINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,3>::Greater(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const XMINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,3>::GreaterOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Equal(const XMINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,3>::Equal(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool NotEqual(const XMINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,3>::NotEqual(v1, std::forward<V>(v2));
        }
    };

    template <>
    struct Vector_Comparator<XMINT4>
    {
        static __forceinline bool Less(const XMINT4 &v1, const XMINT4 &v2)
        {
            return XMVectorAdapter<int32_t,4>::Less(v1,v2);
        }

        template <class V>
        static __forceinline bool LessOrEqual(const XMINT4 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,4>::LessOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Greater(const XMINT4 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,4>::Greater(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const XMINT4 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,4>::GreaterOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Equal(const XMINT4 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,4>::Equal(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool NotEqual(const XMINT4 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,4>::NotEqual(v1, std::forward<V>(v2));
        }
    };

    template <>
    struct Vector_Comparator<XMFLOAT2>
    {
        static __forceinline bool Less(const XMFLOAT2 &v1, const XMFLOAT2 &v2)
        {
            return XMVectorAdapter<float_t,2>::Less(v1,v2);
        }

        template <class V>
        static __forceinline bool LessOrEqual(const XMFLOAT2 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,2>::LessOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Greater(const XMFLOAT2 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,2>::Greater(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const XMFLOAT2 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,2>::GreaterOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Equal(const XMFLOAT2 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,2>::Equal(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool NotEqual(const XMFLOAT2 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,2>::NotEqual(v1, std::forward<V>(v2));
        }
    };

    template <>
    struct Vector_Comparator<XMFLOAT3>
    {
        static __forceinline bool Less(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return XMVectorAdapter<float_t,3>::Less(v1,v2);
        }

        template <class V>
        static __forceinline bool LessOrEqual(const XMFLOAT3 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,3>::LessOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Greater(const XMFLOAT3 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,3>::Greater(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const XMFLOAT3 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,3>::GreaterOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Equal(const XMFLOAT3 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,3>::Equal(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool NotEqual(const XMFLOAT3 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,3>::NotEqual(v1, std::forward<V>(v2));
        }
    };

    template <>
    struct Vector_Comparator<XMFLOAT4>
    {
        static __forceinline bool Less(const XMFLOAT4 &v1, const XMFLOAT4 &v2)
        {
            return XMVectorAdapter<float_t,4>::Less(v1,v2);
        }

        template <class V>
        static __forceinline bool LessOrEqual(const XMFLOAT4 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,4>::LessOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Greater(const XMFLOAT4 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,4>::Greater(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const XMFLOAT4 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,4>::GreaterOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Equal(const XMFLOAT4 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,4>::Equal(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool NotEqual(const XMFLOAT4 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,4>::NotEqual(v1, std::forward<V>(v2));
        }
    };

    template <>
    struct Vector_Comparator<XMUINT2>
    {
        static __forceinline bool Less(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return XMVectorAdapter<uint32_t,2>::Less(v1,v2);
        }

        template <class V>
        static __forceinline bool LessOrEqual(const XMUINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,2>::LessOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Greater(const XMUINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,2>::Greater(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const XMUINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,2>::GreaterOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Equal(const XMUINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,2>::Equal(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool NotEqual(const XMUINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,2>::NotEqual(v1, std::forward<V>(v2));
        }
    };

    template <>
    struct Vector_Comparator<XMUINT3>
    {
        static __forceinline bool Less(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return XMVectorAdapter<uint32_t,3>::Less(v1,v2);
        }

        template <class V>
        static __forceinline bool LessOrEqual(const XMUINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,3>::LessOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Greater(const XMUINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,3>::Greater(v1, std::forward<V>(v2));
        }
        
        template <class V>
        static __forceinline bool GreaterOrEqual(const XMUINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,3>::GreaterOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Equal(const XMUINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,3>::Equal(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool NotEqual(const XMUINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,3>::NotEqual(v1, std::forward<V>(v2));
        }
    };

    template <>
    struct Vector_Comparator<XMUINT4>
    {
        static __forceinline bool Less(const XMUINT4 &v1, const XMUINT4 &v2)
        {
            return XMVectorAdapter<uint32_t,4>::Less(v1,v2);
        }

        template <class V>
        static __forceinline bool LessOrEqual(const XMUINT4 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,4>::LessOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Greater(const XMUINT4 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,4>::Greater(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool GreaterOrEqual(const XMUINT4 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,4>::GreaterOrEqual(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool Equal(const XMUINT4 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,4>::Equal(v1, std::forward<V>(v2));
        }
        template <class V>
        static __forceinline bool NotEqual(const XMUINT4 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,4>::NotEqual(v1, std::forward<V>(v2));
        }
    };
}

namespace
{
    template <class V>
    struct Vector_Geometry;

    template <>
    struct Vector_Geometry<XMINT2>
    {
        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const XMINT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,2>::AngleBetweenNormals(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const XMINT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,2>::AngleBetweenVectors(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const XMINT2 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<int32_t,2>::ClampLength(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const XMINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,2>::CrossProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const XMINT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,2>::DotProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool InBounds(const XMINT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,2>::InBounds(v1, std::forward<V>(v2));
        }

        static __forceinline XMVECTOR Length(const XMINT2 &v) noexcept
        {
            return XMVectorAdapter<int32_t,2>::Length(v);
        }

        static __forceinline XMVECTOR LengthSq(const XMINT2 &v) noexcept
        {
            return XMVectorAdapter<int32_t,2>::LengthSq(v);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR LinePointDistance(const XMINT2 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<int32_t,2>::LinePointDistance(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        static __forceinline XMVECTOR Normalize(const XMINT2 &v) noexcept
        {
            return XMVectorAdapter<int32_t,2>::Normalize(v);
        }

        static __forceinline XMVECTOR Orthogonal(const XMINT2 &v) noexcept
        {
            return XMVectorAdapter<int32_t,2>::Orthogonal(v);
        }

        static __forceinline XMVECTOR ReciprocalLength(const XMINT2 &v) noexcept
        {
            return XMVectorAdapter<int32_t,2>::ReciprocalLength(v);
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const XMINT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,2>::Reflect(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const XMINT2 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<int32_t,2>::Refract(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMINT3>
    {
        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const XMINT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,3>::AngleBetweenNormals(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const XMINT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,3>::AngleBetweenVectors(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const XMINT3 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<int32_t,3>::ClampLength(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const XMINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<int32_t,3>::CrossProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const XMINT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,3>::DotProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool InBounds(const XMINT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,3>::InBounds(v1, std::forward<V>(v2));
        }

        static __forceinline XMVECTOR Length(const XMINT3 &v) noexcept
        {
            return XMVectorAdapter<int32_t,3>::Length(v);
        }

        static __forceinline XMVECTOR LengthSq(const XMINT3 &v) noexcept
        {
            return XMVectorAdapter<int32_t,3>::LengthSq(v);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR LinePointDistance(const XMINT3 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<int32_t,3>::LinePointDistance(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        static __forceinline XMVECTOR Normalize(const XMINT3 &v) noexcept
        {
            return XMVectorAdapter<int32_t,3>::Normalize(v);
        }

        static __forceinline XMVECTOR Orthogonal(const XMINT3 &v) noexcept
        {
            return XMVectorAdapter<int32_t,3>::Orthogonal(v);
        }

        static __forceinline XMVECTOR ReciprocalLength(const XMINT3 &v) noexcept
        {
            return XMVectorAdapter<int32_t,3>::ReciprocalLength(v);
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const XMINT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,3>::Reflect(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const XMINT3 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<int32_t,3>::Refract(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMINT4>
    {
        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const XMINT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,4>::AngleBetweenNormals(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const XMINT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,4>::AngleBetweenVectors(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const XMINT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<int32_t,4>::ClampLength(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR CrossProduct(const XMINT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<int32_t,4>::CrossProduct(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const XMINT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,4>::DotProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool InBounds(const XMINT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,4>::InBounds(v1, std::forward<V>(v2));
        }

        static __forceinline XMVECTOR Length(const XMINT4 &v) noexcept
        {
            return XMVectorAdapter<int32_t,4>::Length(v);
        }

        static __forceinline XMVECTOR LengthSq(const XMINT4 &v) noexcept
        {
            return XMVectorAdapter<int32_t,4>::LengthSq(v);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR LinePointDistance(const XMINT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<int32_t,4>::LinePointDistance(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        static __forceinline XMVECTOR Normalize(const XMINT4 &v) noexcept
        {
            return XMVectorAdapter<int32_t,4>::Normalize(v);
        }

        static __forceinline XMVECTOR Orthogonal(const XMINT4 &v) noexcept
        {
            return XMVectorAdapter<int32_t,4>::Orthogonal(v);
        }

        static __forceinline XMVECTOR ReciprocalLength(const XMINT4 &v) noexcept
        {
            return XMVectorAdapter<int32_t,4>::ReciprocalLength(v);
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const XMINT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<int32_t,4>::Reflect(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const XMINT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<int32_t,4>::Refract(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT2>
    {
        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const XMFLOAT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,2>::AngleBetweenNormals(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const XMFLOAT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,2>::AngleBetweenVectors(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const XMFLOAT2 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<float_t,2>::ClampLength(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const XMFLOAT2 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,2>::CrossProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const XMFLOAT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,2>::DotProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool InBounds(const XMFLOAT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,2>::InBounds(v1, std::forward<V>(v2));
        }

        static __forceinline XMVECTOR Length(const XMFLOAT2 &v) noexcept
        {
            return XMVectorAdapter<float_t,2>::Length(v);
        }

        static __forceinline XMVECTOR LengthSq(const XMFLOAT2 &v) noexcept
        {
            return XMVectorAdapter<float_t,2>::LengthSq(v);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR LinePointDistance(const XMFLOAT2 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<float_t,2>::LinePointDistance(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        static __forceinline XMVECTOR Normalize(const XMFLOAT2 &v) noexcept
        {
            return XMVectorAdapter<float_t,2>::Normalize(v);
        }

        static __forceinline XMVECTOR Orthogonal(const XMFLOAT2 &v) noexcept
        {
            return XMVectorAdapter<float_t,2>::Orthogonal(v);
        }

        static __forceinline XMVECTOR ReciprocalLength(const XMFLOAT2 &v) noexcept
        {
            return XMVectorAdapter<float_t,2>::ReciprocalLength(v);
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const XMFLOAT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,2>::Reflect(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const XMFLOAT2 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<float_t,2>::Refract(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT3>
    {
        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const XMFLOAT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,3>::AngleBetweenNormals(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const XMFLOAT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,3>::AngleBetweenVectors(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const XMFLOAT3 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<float_t,3>::ClampLength(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const XMFLOAT3 &v1, V &&v2)
        {
            return XMVectorAdapter<float_t,3>::CrossProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const XMFLOAT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,3>::DotProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool InBounds(const XMFLOAT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,3>::InBounds(v1, std::forward<V>(v2));
        }

        static __forceinline XMVECTOR Length(const XMFLOAT3 &v) noexcept
        {
            return XMVectorAdapter<float_t,3>::Length(v);
        }

        static __forceinline XMVECTOR LengthSq(const XMFLOAT3 &v) noexcept
        {
            return XMVectorAdapter<float_t,3>::LengthSq(v);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR LinePointDistance(const XMFLOAT3 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<float_t,3>::LinePointDistance(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        static __forceinline XMVECTOR Normalize(const XMFLOAT3 &v) noexcept
        {
            return XMVectorAdapter<float_t,3>::Normalize(v);
        }

        static __forceinline XMVECTOR Orthogonal(const XMFLOAT3 &v) noexcept
        {
            return XMVectorAdapter<float_t,3>::Orthogonal(v);
        }

        static __forceinline XMVECTOR ReciprocalLength(const XMFLOAT3 &v) noexcept
        {
            return XMVectorAdapter<float_t,3>::ReciprocalLength(v);
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const XMFLOAT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,3>::Reflect(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const XMFLOAT3 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<float_t,3>::Refract(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT4>
    {
        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const XMFLOAT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,4>::AngleBetweenNormals(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const XMFLOAT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,4>::AngleBetweenVectors(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const XMFLOAT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<float_t,4>::ClampLength(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR CrossProduct(const XMFLOAT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<float_t,4>::CrossProduct(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const XMFLOAT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,4>::DotProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool InBounds(const XMFLOAT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,4>::InBounds(v1, std::forward<V>(v2));
        }

        static __forceinline XMVECTOR Length(const XMFLOAT4 &v) noexcept
        {
            return XMVectorAdapter<float_t,4>::Length(v);
        }

        static __forceinline XMVECTOR LengthSq(const XMFLOAT4 &v) noexcept
        {
            return XMVectorAdapter<float_t,4>::LengthSq(v);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR LinePointDistance(const XMFLOAT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<float_t,4>::LinePointDistance(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        static __forceinline XMVECTOR Normalize(const XMFLOAT4 &v) noexcept
        {
            return XMVectorAdapter<float_t,4>::Normalize(v);
        }

        static __forceinline XMVECTOR Orthogonal(const XMFLOAT4 &v) noexcept
        {
            return XMVectorAdapter<float_t,4>::Orthogonal(v);
        }

        static __forceinline XMVECTOR ReciprocalLength(const XMFLOAT4 &v) noexcept
        {
            return XMVectorAdapter<float_t,4>::ReciprocalLength(v);
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const XMFLOAT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<float_t,4>::Reflect(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const XMFLOAT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<float_t,4>::Refract(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMUINT2>
    {
        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const XMUINT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::AngleBetweenNormals(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const XMUINT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::AngleBetweenVectors(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const XMUINT2 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::ClampLength(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const XMUINT2 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,2>::CrossProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const XMUINT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::DotProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool InBounds(const XMUINT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::InBounds(v1, std::forward<V>(v2));
        }

        static __forceinline XMVECTOR Length(const XMUINT2 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::Length(v);
        }

        static __forceinline XMVECTOR LengthSq(const XMUINT2 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::LengthSq(v);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR LinePointDistance(const XMUINT2 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::LinePointDistance(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        static __forceinline XMVECTOR Normalize(const XMUINT2 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::Normalize(v);
        }

        static __forceinline XMVECTOR Orthogonal(const XMUINT2 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::Orthogonal(v);
        }

        static __forceinline XMVECTOR ReciprocalLength(const XMUINT2 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::ReciprocalLength(v);
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const XMUINT2 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::Reflect(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const XMUINT2 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<uint32_t,2>::Refract(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMUINT3>
    {
        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const XMUINT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::AngleBetweenNormals(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const XMUINT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::AngleBetweenVectors(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const XMUINT3 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::ClampLength(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static __forceinline XMVECTOR CrossProduct(const XMUINT3 &v1, V &&v2)
        {
            return XMVectorAdapter<uint32_t,3>::CrossProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const XMUINT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::DotProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool InBounds(const XMUINT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::InBounds(v1, std::forward<V>(v2));
        }

        static __forceinline XMVECTOR Length(const XMUINT3 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::Length(v);
        }

        static __forceinline XMVECTOR LengthSq(const XMUINT3 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::LengthSq(v);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR LinePointDistance(const XMUINT3 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::LinePointDistance(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        static __forceinline XMVECTOR Normalize(const XMUINT3 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::Normalize(v);
        }

        static __forceinline XMVECTOR Orthogonal(const XMUINT3 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::Orthogonal(v);
        }

        static __forceinline XMVECTOR ReciprocalLength(const XMUINT3 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::ReciprocalLength(v);
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const XMUINT3 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::Reflect(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const XMUINT3 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<uint32_t,3>::Refract(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMUINT4>
    {
        template <class V>
        static __forceinline XMVECTOR AngleBetweenNormals(const XMUINT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::AngleBetweenNormals(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline XMVECTOR AngleBetweenVectors(const XMUINT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::AngleBetweenVectors(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR ClampLength(const XMUINT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::ClampLength(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR CrossProduct(const XMUINT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::CrossProduct(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static __forceinline XMVECTOR DotProduct(const XMUINT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::DotProduct(v1, std::forward<V>(v2));
        }

        template <class V>
        static __forceinline bool InBounds(const XMUINT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::InBounds(v1, std::forward<V>(v2));
        }

        static __forceinline XMVECTOR Length(const XMUINT4 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::Length(v);
        }

        static __forceinline XMVECTOR LengthSq(const XMUINT4 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::LengthSq(v);
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR LinePointDistance(const XMUINT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::LinePointDistance(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }

        static __forceinline XMVECTOR Normalize(const XMUINT4 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::Normalize(v);
        }

        static __forceinline XMVECTOR Orthogonal(const XMUINT4 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::Orthogonal(v);
        }

        static __forceinline XMVECTOR ReciprocalLength(const XMUINT4 &v) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::ReciprocalLength(v);
        }

        template <class V>
        static __forceinline XMVECTOR Reflect(const XMUINT4 &v1, V &&v2) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::Reflect(v1, std::forward<V>(v2));
        }

        template <class V2, class V3>
        static __forceinline XMVECTOR Refract(const XMUINT4 &v1, V2 &&v2, V3 &&v3) noexcept
        {
            return XMVectorAdapter<uint32_t,4>::Refract(v1, std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };
}

template <class V>
inline bool operator<(const V &vector1, const V &vector2)
{
    return Vector_Comparator<V>::Less(vector1, vector2);
}

template <class V1, class V2>
inline bool operator<=(V1 &&vector1, V2 &&vector2)
{
    return Vector_Comparator<std::decay_t<V1>>::LessOrEqual(std::forward<V1>(vector1), std::forward<V2>(vector2));
}

template <class V1, class V2>
inline bool operator>(V1 &&vector1, V2 &&vector2)
{
    return Vector_Comparator<std::decay_t<V1>>::Greater(std::forward<V1>(vector1), std::forward<V2>(vector2));
}

template <class V1, class V2>
inline bool operator>=(V1 &&vector1, V2 &&vector2)
{
    return Vector_Comparator<std::decay_t<V1>>::GreaterOrEqual(std::forward<V1>(vector1), std::forward<V2>(vector2));
}

template <class V1, class V2>
inline bool operator==(V1 &&vector1, V2 &&vector2)
{
    return Vector_Comparator<std::decay_t<V1>>::Equal(std::forward<V1>(vector1), std::forward<V2>(vector2));
}

template <class V1, class V2>
inline bool operator!=(V1 &&vector1, V2 &&vector2)
{
    return Vector_Comparator<std::decay_t<V1>>::NotEqual(std::forward<V1>(vector1), std::forward<V2>(vector2));
}

namespace VectorAngle
{
    /// <summary>Computes the radian angle between two 2-, 3- or 4D vectors.</summary>
    template <class V1, class V2>
    inline XMVECTOR AngleBetweenVectors(V1 &&vector1, V2 &&vector2) noexcept
    {
        return Vector_Geometry<std::decay_t<V1>>::AngleBetweenVectors(std::forward<V1>(vector1), std::forward<V2>(vector2));
    }

    /// <summary>Computes the radian angle between two normalized 2-, 3- or 4D vectors.</summary>
    template <class V1, class V2>
    inline XMVECTOR AngleBetweenNormals(V1 &&vector1, V2 &&vector2) noexcept
    {
        return Vector_Geometry<std::decay_t<V1>>::AngleBetweenNormals(std::forward<V1>(vector1), std::forward<V2>(vector2));
    }
}

/// <summary> Clamps the length of a 2-, 3- or 4D vector to a given range.</summary>
template <class V1, class V2, class V3>
inline XMVECTOR ClampLength(V1 &&vector, V2 &&lengthMin, V3 &&lengthMax) noexcept
{
    return Vector_Geometry<std::decay_t<V1>>::ClampLength(std::forward<V1>(vector), std::forward<V2>(lengthMin), std::forward<V3>(lengthMax));
}

/// <summary>
/// Depending on the argument type computes:
/// <para/>• the 2D cross product;
/// <para/>• the cross product between two 3D vectors;
/// <para/>• the cross product between three 4D vectors;
/// </summary>
template <class V1, class ... V2>
inline XMVECTOR CrossProduct(V1&& vector1, V2&& ...vector2) noexcept
{
    return Vector_Geometry<std::decay_t<V1>>::CrossProduct(std::forward<V1>(vector1), std::forward<V2>(vector2)...);
}

/// <summary>Computes the dot product between two vectors.</summary>
template <class V1, class V2>
inline XMVECTOR DotProduct(V1&& vector1, V2&& vector2) noexcept
{
    return Vector_Geometry<std::decay_t<V1>>::DotProduct(std::forward<V1>(vector1), std::forward<V2>(vector2));
}

/// <summary>Tests whether the components of a 2-, 3- or 4D vector are within set bounds.</summary>
template <class V1, class V2>
inline bool InBounds(V1 &&vector1, V2 &&vector2) noexcept
{
    return Vector_Geometry<std::decay_t<V1>>::InBounds(std::forward<V1>(vector1), std::forward<V2>(vector2));
}

/// <summary>Computes the length of a 2-, 3- or 4D vector.</summary>
template <class V>
inline XMVECTOR Length(V&& vector) noexcept
{
    return Vector_Geometry<std::decay_t<V>>::Length(std::forward<V>(vector));
}

/// <summary>Computes the square of the length of a 2-, 3- or 4D vector.</summary>
template <class V>
inline XMVECTOR LengthSq(V&& vector) noexcept
{
    return Vector_Geometry<std::decay_t<V>>::LengthSq(std::forward<V>(vector));
}

/// <summary>Computes the length of a 2-, 3- or 4D vector (same as Length).</summary>
template <class V>
inline XMVECTOR Magnitude(V&& vector) noexcept
{
    return Vector_Geometry<std::decay_t<V>>::Length(std::forward<V>(vector));
}

/// <summary>Returns the normalized version of a 2-, 3- or 4D vector.</summary>
template <class V>
inline XMVECTOR Normalize(V&& vector) noexcept
{
    return Vector_Geometry<std::decay_t<V>>::Normalize(std::forward<V>(vector));
}

 /// <summary>Computes the minimum distance between a line and a point.</summary>
template <class V1, class V2, class V3>
inline XMVECTOR LinePointDistance(V1 &&linePoint1, V2 &&linePoint2, V3 &&point) noexcept
{
    return Vector_Geometry<std::decay_t<V1>>::LinePointDistance(
        std::forward<V1>(linePoint1), std::forward<V2>(linePoint2), std::forward<V3>(point)
    );
}

/// <summary>Computes a vector perpendicular to a 2-, 3- or 4D vector.</summary>
template <class V>
inline XMVECTOR OrthogonalVector(V&& vector) noexcept
{
    return Vector_Geometry<std::decay_t<V>>::Orthogonal(std::forward<V>(vector));
}

/// <summary>Computes the reciprocal of the length of a 2-, 3- or 4D vector.</summary>
template <class V>
inline XMVECTOR ReciprocalLength(V&& vector) noexcept
{
    return Vector_Geometry<std::decay_t<V>>::ReciprocalLength(std::forward<V>(vector));
}

/// <summary> Reflects an incident 2-, 3- or 4D vector across a corresponding 2-, 3- or 4D normal vector.</summary>
template <class V1, class V2>
inline XMVECTOR Reflect(V1 &&vector, V2 &&normal) noexcept
{
    return Vector_Geometry<std::decay_t<V1>>::Reflect(std::forward<V1>(vector), std::forward<V2>(normal));
}

/// <summary> Refracts an incident 2-, 3- or 4D vector across a corresponding 2-, 3- or 4D normal vector.</summary>
template <class V1, class V2, class V3>
inline XMVECTOR Refract(V1 &&vector, V2 &&normal, V3 &&refractionIndex) noexcept
{
    return Vector_Geometry<std::decay_t<V1>>::Refract(
        std::forward<V1>(vector), std::forward<V2>(normal), std::forward<V3>(refractionIndex)
    );
}

template <class V, class M>
inline auto operator*(const V &vector, const M &matrix)
{
    if constexpr (sizeof(V) < sizeof(M)) {
        return TransformMapper<V,M>::Transform(vector, matrix);
    } else {
        return TransformMapper<M,V>::Transform(matrix, vector);
    }
}
