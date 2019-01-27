#pragma once

#include <DirectXMath.h>

namespace
{
    using namespace DirectX;

    template <class T, int rows, int columns>
    struct Matrix_Helper;

    template <class T>
    struct Matrix_Helper<T, 3, 3>
    {
        typedef ::DirectX::XMFLOAT3X3 Type;

        template <class M>
        static inline auto Multiply(const Type &lhs, const M &rhs);

        template <>
        static inline auto Multiply<XMMATRIX>(const Type &lhs, const XMMATRIX &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat3x3(&lhs), rhs);
        }

        template <>
        static inline auto Multiply<XMFLOAT3X3>(const Type &lhs, const XMFLOAT3X3 &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat3x3(&lhs), XMLoadFloat3x3(&rhs));
        }

        template <>
        static inline auto Multiply<XMFLOAT3X4>(const Type &lhs, const XMFLOAT3X4 &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat3x3(&lhs), XMLoadFloat3x4(&rhs));
        }

        static inline auto Transpose(const Type &matrix)
        {
            return XMMatrixTranspose(XMLoadFloat3x3(&matrix));
        }
    };

    template <class T>
    struct Matrix_Helper<T, 3, 4>
    {
        typedef ::DirectX::XMFLOAT3X4 Type;

        template <class M>
        static inline auto Multiply(const Type &lhs, const M &rhs);

        template <>
        static inline auto Multiply<XMMATRIX>(const Type &lhs, const XMMATRIX &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat3x4(&lhs), rhs);
        }

        template <>
        static inline auto Multiply<XMFLOAT4X3>(const Type &lhs, const XMFLOAT4X3 &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat3x4(&lhs), XMLoadFloat4x3(&rhs));
        }

        template <>
        static inline auto Multiply<XMFLOAT4X4>(const Type &lhs, const XMFLOAT4X4 &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat3x4(&lhs), XMLoadFloat4x4(&rhs));
        }

        static inline auto Transpose(const Type &matrix)
        {
            return XMMatrixTranspose(XMLoadFloat3x4(&matrix));
        }
    };

    template <class T>
    struct Matrix_Helper<T, 4, 3>
    {
        typedef ::DirectX::XMFLOAT4X3 Type;

        template <class M>
        static inline auto Multiply(const Type &lhs, const M &rhs);

        template <>
        static inline auto Multiply<XMMATRIX>(const Type &lhs, const XMMATRIX &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat4x3(&lhs), rhs);
        }

        template <>
        static inline auto Multiply<XMFLOAT3X3>(const Type &lhs, const XMFLOAT3X3 &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat4x3(&lhs), XMLoadFloat3x3(&rhs));
        }

        template <>
        static inline auto Multiply<XMFLOAT3X4>(const Type &lhs, const XMFLOAT3X4 &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat4x3(&lhs), XMLoadFloat3x4(&rhs));
        }

        static inline auto Transpose(const Type &matrix)
        {
            return XMMatrixTranspose(XMLoadFloat4x3(&matrix));
        }
    };

    template <class T>
    struct Matrix_Helper<T, 4, 4>
    {
        typedef ::DirectX::XMFLOAT4X4 Type;

        template <class M>
        static inline auto Multiply(const Type &lhs, const M &rhs);

        template <>
        static inline auto Multiply<XMMATRIX>(const Type &lhs, const XMMATRIX &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat4x4(&lhs), rhs);
        }

        template <>
        static inline auto Multiply<XMFLOAT4X3>(const Type &lhs, const XMFLOAT4X3 &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat4x4(&lhs), XMLoadFloat4x3(&rhs));
        }

        template <>
        static inline auto Multiply<XMFLOAT4X4>(const Type &lhs, const XMFLOAT4X4 &rhs)
        {
            return XMMatrixMultiply(XMLoadFloat4x4(&lhs), XMLoadFloat4x4(&rhs));
        }

        static inline auto Transpose(const Type &matrix)
        {
            return XMMatrixTranspose(XMLoadFloat4x4(&matrix));
        }
    };
}

template <class T, int rows, int columns>
using Matrix_Helper_T = typename Matrix_Helper<T, rows, columns>::Type;

#define CHECK_ARGUMENT_TYPE(CompType, Result, Type)                                           \
    constexpr bool Result = std::is_same_v<std::decay_t<##CompType>, ##Type>;                 \
    static_assert(std::bool_constant<Result>::value, "No matching overload for " __FUNCTION__ )

#define CHECK_ARGUMENT_TYPE_2(CompType, Result1, Type1, Result2, Type2)        \
    using BaseType = std::decay_t<##CompType>;                                 \
                                                                               \
    constexpr bool Result1 = std::is_same_v<BaseType, ##Type1>;                \
    constexpr bool Result2 = std::is_same_v<BaseType, ##Type2>;                \
                                                                               \
    static_assert(Result1 || Result2, "No matching overload for " __FUNCTION__ )

#define CHECK_ARGUMENT_TYPE_3(CompType, Result1, Type1, Result2, Type2, Type3, Result3)   \
    using BaseType = std::decay_t<##CompType>;                                            \
                                                                                          \
    constexpr bool Result1 = std::is_same_v<BaseType, ##Type1>;                           \
    constexpr bool Result2 = std::is_same_v<BaseType, ##Type2>;                           \
    constexpr bool Result3 = std::is_same_v<BaseType, ##Type3>;                           \
                                                                                          \
    static_assert(Result1 || Result2 || Result3, "No matching overload for " __FUNCTION__ )

namespace
{
    using namespace DirectX;

    template <class T, int length>
    struct Vector_Helper;

    template <>
    struct Vector_Helper<int32_t, 2>
    {
        typedef ::DirectX::XMINT2 Type;

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenNormals(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2AngleBetweenNormals(XMLoadSInt2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2AngleBetweenNormals(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenVectors(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2AngleBetweenVectors(XMLoadSInt2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2AngleBetweenVectors(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&vec, V2 &&min, V3 &&max) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2ClampLengthV(XMLoadSInt2(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
            else if (isSameType) {
                return XMVector2ClampLengthV(XMLoadSInt2(&vec), XMLoadSInt2(&min), XMLoadSInt2(&max));
            }
        }

        template <class V>
        static inline XMVECTOR ClampLength(V &&vec, float_t min, float_t max) noexcept
        {
            return XMVector2ClampLength(XMLoadSInt2(&vec), min, max);
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Cross(XMLoadSInt2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2Cross(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
        }

        static inline auto DotProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector2Dot(XMLoadSInt2(&lhs), XMLoadSInt2(&rhs));
        }

        static inline bool Equal(const Type &lhs, const Type &rhs)
        {
            return XMVector2EqualInt(XMLoadSInt2(&lhs), XMLoadSInt2(&rhs));
        }

        static inline bool Greater(const Type &lhs, const Type &rhs)
        {
            return XMVector2Greater(XMLoadSInt2(&lhs), XMLoadSInt2(&rhs));
        }

        static inline bool GreaterOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2GreaterOrEqual(XMLoadSInt2(&lhs), XMLoadSInt2(&rhs));
        }

        static inline auto Length(const Type &vec)
        {
            return XMVector2Length(XMLoadSInt2(&vec));
        }

        static inline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector2Less(XMLoadSInt2(&lhs), XMLoadSInt2(&rhs));
        }

        static inline bool LessOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2LessOrEqual(XMLoadSInt2(&lhs), XMLoadSInt2(&rhs));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V3, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2LinePointDistance(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2) std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector2LinePointDistance(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2) XMLoadSInt2(&vec3));
            }
        }

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2NotEqualInt(XMLoadSInt2(&lhs), XMLoadSInt2(&rhs));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Normalize(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector2Normalize(XMLoadSInt2(&vec));
            }
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Orthogonal(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector2Orthogonal(XMLoadSInt2(&vec));
            }
        }

        static inline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector2ReciprocalLength(XMLoadSInt2(&vec));
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Reflect(XMLoadSInt2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2Reflect(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2RefractV(XMLoadSInt2(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector2RefractV(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2), XMLoadSInt2(&vec3));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, float index) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Refract(XMLoadSInt2(&vec1), std::forward<V2>(vec2), index);
            }
            else if (isSameType) {
                return XMVector2Refract(XMLoadSInt2(&vec1), XMLoadSInt2(&vec2), index);
            }
        }

        template <class M>
        static inline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static inline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), mat);
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<int32_t, 3>
    {
        typedef ::DirectX::XMINT3 Type;

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenNormals(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3AngleBetweenNormals(XMLoadSInt3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3AngleBetweenNormals(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenVectors(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3AngleBetweenVectors(XMLoadSInt3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3AngleBetweenVectors(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&vec, V2 &&min, V3 &&max) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3ClampLengthV(XMLoadSInt3(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
            else if (isSameType) {
                return XMVector3ClampLengthV(XMLoadSInt3(&vec), XMLoadSInt3(&min), XMLoadSInt3(&max));
            }
        }

        template <class V>
        static inline XMVECTOR ClampLength(V &&vec, float_t min, float_t max) noexcept
        {
            return XMVector3ClampLength(XMLoadSInt3(&vec), min, max);
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Cross(XMLoadSInt3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3Cross(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
        }

        static inline auto DotProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector3Dot(XMLoadSInt3(&lhs), XMLoadSInt3(&rhs));
        }

        static inline bool Equal(const Type &lhs, const Type &rhs)
        {
            return XMVector3EqualInt(XMLoadSInt3(&lhs), XMLoadSInt3(&rhs));
        }

        static inline bool Greater(const Type &lhs, const Type &rhs)
        {
            return XMVector3Greater(XMLoadSInt3(&lhs), XMLoadSInt3(&rhs));
        }

        static inline bool GreaterOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3GreaterOrEqual(XMLoadSInt3(&lhs), XMLoadSInt3(&rhs));
        }

        static inline auto Length(const Type &vec)
        {
            return XMVector3Length(XMLoadSInt3(&vec));
        }

        static inline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector3Less(XMLoadSInt3(&lhs), XMLoadSInt3(&rhs));
        }

        static inline bool LessOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3LessOrEqual(XMLoadSInt3(&lhs), XMLoadSInt3(&rhs));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V3, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3LinePointDistance(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2) std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector3LinePointDistance(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2) XMLoadSInt3(&vec3));
            }
        }

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3NotEqualInt(XMLoadSInt3(&lhs), XMLoadSInt3(&rhs));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Normalize(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector3Normalize(XMLoadSInt3(&vec));
            }
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Orthogonal(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector3Orthogonal(XMLoadSInt3(&vec));
            }
        }

        static inline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector3ReciprocalLength(XMLoadSInt3(&vec));
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Reflect(XMLoadSInt3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3Reflect(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3RefractV(XMLoadSInt3(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector3RefractV(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2), XMLoadSInt3(&vec3));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, float index) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Refract(XMLoadSInt3(&vec1), std::forward<V2>(vec2), index);
            }
            else if (isSameType) {
                return XMVector3Refract(XMLoadSInt3(&vec1), XMLoadSInt3(&vec2), index);
            }
        }

        template <class M>
        static inline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static inline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), mat);
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<int32_t, 4>
    {
        typedef ::DirectX::XMINT4 Type;

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenNormals(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4AngleBetweenNormals(XMLoadSInt4(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector4AngleBetweenNormals(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenVectors(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4AngleBetweenVectors(XMLoadSInt4(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector4AngleBetweenVectors(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&vec, V2 &&min, V3 &&max) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4ClampLengthV(XMLoadSInt4(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
            else if (isSameType) {
                return XMVector4ClampLengthV(XMLoadSInt4(&vec), XMLoadSInt4(&min), XMLoadSInt4(&max));
            }
        }

        template <class V>
        static inline XMVECTOR ClampLength(V &&vec, float_t min, float_t max) noexcept
        {
            return XMVector4ClampLength(XMLoadSInt4(&vec), min, max);
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR CrossProduct(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Cross(XMLoadSInt4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector4Cross(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2), XMLoadSInt4(&vec3));
            }
        }

        static inline auto DotProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector4Dot(XMLoadSInt4(&lhs), XMLoadSInt4(&rhs));
        }

        static inline bool Equal(const Type &lhs, const Type &rhs)
        {
            return XMVector2EqualInt(XMLoadSInt4(&lhs), XMLoadSInt4(&rhs));
        }

        static inline bool Greater(const Type &lhs, const Type &rhs)
        {
            return XMVector2Greater(XMLoadSInt4(&lhs), XMLoadSInt4(&rhs));
        }

        static inline bool GreaterOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4GreaterOrEqual(XMLoadSInt4(&lhs), XMLoadSInt4(&rhs));
        }

        static inline auto Length(const Type &vec)
        {
            return XMVector4Length(XMLoadSInt4(&vec));
        }

        static inline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector4Less(XMLoadSInt4(&lhs), XMLoadSInt4(&rhs));
        }

        static inline bool LessOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4LessOrEqual(XMLoadSInt4(&lhs), XMLoadSInt4(&rhs));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V3, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4LinePointDistance(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2) std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector4LinePointDistance(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2) XMLoadSInt4(&vec3));
            }
        }

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4NotEqualInt(XMLoadSInt4(&lhs), XMLoadSInt4(&rhs));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Normalize(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector4Normalize(XMLoadSInt4(&vec));
            }
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Orthogonal(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector4Orthogonal(XMLoadSInt4(&vec));
            }
        }

        static inline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector4ReciprocalLength(XMLoadSInt4(&vec));
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Reflect(XMLoadSInt4(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector4Reflect(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4RefractV(XMLoadSInt4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector4RefractV(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2), XMLoadSInt4(&vec3));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, float index) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Refract(XMLoadSInt4(&vec1), std::forward<V2>(vec2), index);
            }
            else if (isSameType) {
                return XMVector4Refract(XMLoadSInt4(&vec1), XMLoadSInt4(&vec2), index);
            }
        }

        template <class M>
        static inline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static inline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector4Transform(XMLoadSInt4(&vec), mat);
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector4Transform(XMLoadSInt4(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector4Transform(XMLoadSInt4(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<float_t, 2>
    {
        typedef ::DirectX::XMFLOAT2 Type;

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenNormals(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2AngleBetweenNormals(XMLoadFloat2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2AngleBetweenNormals(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenVectors(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2AngleBetweenVectors(XMLoadFloat2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2AngleBetweenVectors(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&vec, V2 &&min, V3 &&max) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2ClampLengthV(XMLoadFloat2(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
            else if (isSameType) {
                return XMVector2ClampLengthV(XMLoadFloat2(&vec), XMLoadFloat2(&min), XMLoadFloat2(&max));
            }
        }

        template <class V>
        static inline XMVECTOR ClampLength(V &&vec, float_t min, float_t max) noexcept
        {
            return XMVector2ClampLength(XMLoadFloat2(&vec), min, max);
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Cross(XMLoadFloat2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2Cross(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
        }

        static inline auto DotProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector2Dot(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs));
        }

        static inline bool Equal(const Type &lhs, const Type &rhs)
        {
            return XMVector2Equal(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs));
        }

        static inline bool Greater(const Type &lhs, const Type &rhs)
        {
            return XMVector2Greater(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs));
        }

        static inline bool GreaterOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2GreaterOrEqual(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs));
        }

        static inline auto Length(const Type &vec)
        {
            return XMVector2Length(XMLoadFloat2(&vec));
        }

        static inline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector2Less(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs));
        }

        static inline bool LessOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2LessOrEqual(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V3, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2LinePointDistance(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2) std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector2LinePointDistance(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2) XMLoadFloat2(&vec3));
            }
        }

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2NotEqual(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Normalize(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector2Normalize(XMLoadFloat2(&vec));
            }
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Orthogonal(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector2Orthogonal(XMLoadFloat2(&vec));
            }
        }

        static inline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector2ReciprocalLength(XMLoadFloat2(&vec));
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Reflect(XMLoadFloat2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2Reflect(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2RefractV(XMLoadFloat2(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector2RefractV(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2), XMLoadFloat2(&vec3));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, float index) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Refract(XMLoadFloat2(&vec1), std::forward<V2>(vec2), index);
            }
            else if (isSameType) {
                return XMVector2Refract(XMLoadFloat2(&vec1), XMLoadFloat2(&vec2), index);
            }
        }

        template <class M>
        static inline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static inline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), mat);
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<float_t, 3>
    {
        typedef ::DirectX::XMFLOAT3 Type;

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenNormals(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3AngleBetweenNormals(XMLoadFloat3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3AngleBetweenNormals(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenVectors(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3AngleBetweenVectors(XMLoadFloat3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3AngleBetweenVectors(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&vec, V2 &&min, V3 &&max) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);
            
            if constexpr (isXMVector) {
                return XMVector3ClampLengthV(XMLoadFloat3(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
            else if (isSameType) {
                return XMVector3ClampLengthV(XMLoadFloat3(&vec), XMLoadFloat3(&min), XMLoadFloat3(&max));
            }
        }

        template <class V>
        static inline XMVECTOR ClampLength(V &&vec, float_t min, float_t max) noexcept
        {
            return XMVector3ClampLength(XMLoadFloat3(&vec), min, max);
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Cross(XMLoadFloat3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3Cross(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
        }

        static inline auto DotProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector3Dot(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs));
        }

        static inline bool Equal(const Type &lhs, const Type &rhs)
        {
            return XMVector3Equal(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs));
        }

        static inline bool Greater(const Type &lhs, const Type &rhs)
        {
            return XMVector3Greater(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs));
        }

        static inline bool GreaterOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3GreaterOrEqual(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs));
        }

        static inline auto Length(const Type &vec)
        {
            return XMVector3Length(XMLoadFloat3(&vec));
        }

        static inline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector3Less(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs));
        }

        static inline bool LessOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3LessOrEqual(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V3, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3LinePointDistance(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2) std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector3LinePointDistance(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2) XMLoadFloat3(&vec3));
            }
        }

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3NotEqual(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Normalize(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector3Normalize(XMLoadFloat3(&vec));
            }
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Orthogonal(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector3Orthogonal(XMLoadFloat3(&vec));
            }
        }

        static inline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector3ReciprocalLength(XMLoadFloat3(&vec));
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Reflect(XMLoadFloat3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3Reflect(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3RefractV(XMLoadFloat3(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector3RefractV(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2), XMLoadFloat3(&vec3));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, float index) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Refract(XMLoadFloat3(&vec1), std::forward<V2>(vec2), index);
            }
            else if (isSameType) {
                return XMVector3Refract(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2), index);
            }
        }

        template <class M>
        static inline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static inline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), mat);
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<float, 4>
    {
        typedef ::DirectX::XMFLOAT4 Type;

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenNormals(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4AngleBetweenNormals(XMLoadFloat4(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector4AngleBetweenNormals(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenVectors(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4AngleBetweenVectors(XMLoadFloat4(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector4AngleBetweenVectors(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&vec, V2 &&min, V3 &&max) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4ClampLengthV(XMLoadFloat4(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
            else if (isSameType) {
                return XMVector4ClampLengthV(XMLoadFloat4(&vec), XMLoadFloat4(&min), XMLoadFloat4(&max));
            }
        }

        template <class V>
        static inline XMVECTOR ClampLength(V &&vec, float_t min, float_t max) noexcept
        {
            return XMVector4ClampLength(XMLoadFloat4(&vec), min, max);
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR CrossProduct(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Cross(XMLoadFloat4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector4Cross(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2), XMLoadFloat4(&vec3));
            }
        }

        static inline auto DotProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector4Dot(XMLoadFloat4(&lhs), XMLoadFloat4(&rhs));
        }

        static inline bool Equal(const Type &lhs, const Type &rhs)
        {
            return XMVector4Equal(XMLoadFloat4(&lhs), XMLoadFloat4(&rhs));
        }

        static inline bool Greater(const Type &lhs, const Type &rhs)
        {
            return XMVector4Greater(XMLoadFloat4(&lhs), XMLoadFloat4(&rhs));
        }

        static inline bool GreaterOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4GreaterOrEqual(XMLoadFloat4(&lhs), XMLoadFloat4(&rhs));
        }

        static inline auto Length(const Type &vec)
        {
            return XMVector4Length(XMLoadFloat4(&vec));
        }

        static inline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector4Less(XMLoadFloat4(&lhs), XMLoadFloat4(&rhs));
        }

        static inline bool LessOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4LessOrEqual(XMLoadFloat4(&lhs), XMLoadFloat4(&rhs));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V3, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4LinePointDistance(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2) std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector4LinePointDistance(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2) XMLoadFloat4(&vec3));
            }
        }

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4NotEqual(XMLoadFloat4(&lhs), XMLoadFloat4(&rhs));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Normalize(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector4Normalize(XMLoadFloat4(&vec));
            }
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Orthogonal(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector4Orthogonal(XMLoadFloat4(&vec));
            }
        }

        static inline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector4ReciprocalLength(XMLoadFloat4(&vec));
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Reflect(XMLoadFloat4(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector4Reflect(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4RefractV(XMLoadFloat4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector4RefractV(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2), XMLoadFloat4(&vec3));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, float index) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Refract(XMLoadFloat4(&vec1), std::forward<V2>(vec2), index);
            }
            else if (isSameType) {
                return XMVector4Refract(XMLoadFloat4(&vec1), XMLoadFloat4(&vec2), index);
            }
        }

        template <class M>
        static inline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static inline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector4Transform(XMLoadFloat4(&vec), mat);
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector4Transform(XMLoadFloat4(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector4Transform(XMLoadFloat4(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<uint32_t, 2>
    {
        typedef ::DirectX::XMUINT2 Type;

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenNormals(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2AngleBetweenNormals(XMLoadUInt2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2AngleBetweenNormals(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenVectors(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2AngleBetweenVectors(XMLoadUInt2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2AngleBetweenVectors(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&vec, V2 &&min, V3 &&max) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2ClampLengthV(XMLoadUInt2(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
            else if (isSameType) {
                return XMVector2ClampLengthV(XMLoadUInt2(&vec), XMLoadUInt2(&min), XMLoadUInt2(&max));
            }
        }

        template <class V>
        static inline XMVECTOR ClampLength(V &&vec, float_t min, float_t max) noexcept
        {
            return XMVector2ClampLength(XMLoadUInt2(&vec), min, max);
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Cross(XMLoadUInt2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2Cross(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
        }

        static inline auto DotProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector2Dot(XMLoadUInt2(&lhs), XMLoadUInt2(&rhs));
        }

        static inline bool Equal(const Type &lhs, const Type &rhs)
        {
            return XMVector2EqualInt(XMLoadUInt2(&lhs), XMLoadUInt2(&rhs));
        }

        static inline bool Greater(const Type &lhs, const Type &rhs)
        {
            return XMVector2Greater(XMLoadUInt2(&lhs), XMLoadUInt2(&rhs));
        }

        static inline bool GreaterOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2GreaterOrEqual(XMLoadUInt2(&lhs), XMLoadUInt2(&rhs));
        }

        static inline auto Length(const Type &vec)
        {
            return XMVector2Length(XMLoadUInt2(&vec));
        }

        static inline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector2Less(XMLoadUInt2(&lhs), XMLoadUInt2(&rhs));
        }

        static inline bool LessOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2LessOrEqual(XMLoadUInt2(&lhs), XMLoadUInt2(&rhs));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V3, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2LinePointDistance(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2) std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector2LinePointDistance(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2) XMLoadUInt3(&vec3));
            }
        }

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2NotEqualInt(XMLoadUInt2(&lhs), XMLoadUInt2(&rhs));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Normalize(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector2Normalize(XMLoadUInt2(&vec));
            }
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Orthogonal(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector2Orthogonal(XMLoadUInt2(&vec));
            }
        }

        static inline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector2ReciprocalLength(XMLoadUInt2(&vec));
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Reflect(XMLoadUInt2(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector2Reflect(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2RefractV(XMLoadUInt2(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector2RefractV(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2), XMLoadUInt2(&vec3));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, float index) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector2Refract(XMLoadUInt2(&vec1), std::forward<V2>(vec2), index);
            }
            else if (isSameType) {
                return XMVector2Refract(XMLoadUInt2(&vec1), XMLoadUInt2(&vec2), index);
            }
        }

        template <class M>
        static inline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static inline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), mat);
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<uint32_t, 3>
    {
        typedef ::DirectX::XMUINT3 Type;

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenNormals(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3AngleBetweenNormals(XMLoadUInt3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3AngleBetweenNormals(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenVectors(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3AngleBetweenVectors(XMLoadUInt3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3AngleBetweenVectors(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&vec, V2 &&min, V3 &&max) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3ClampLengthV(XMLoadUInt3(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
            else if (isSameType) {
                return XMVector3ClampLengthV(XMLoadUInt3(&vec), XMLoadUInt3(&min), XMLoadUInt3(&max));
            }
        }

        template <class V>
        static inline XMVECTOR ClampLength(V &&vec, float_t min, float_t max) noexcept
        {
            return XMVector3ClampLength(XMLoadUInt3(&vec), min, max);
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Cross(XMLoadUInt3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3Cross(XMLoadUInt3(&vec1), XMLoadUInt3(&vec1));
            }
        }

        static inline auto DotProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector3Dot(XMLoadUInt3(&lhs), XMLoadUInt3(&rhs));
        }

        static inline bool Equal(const Type &lhs, const Type &rhs)
        {
            return XMVector3EqualInt(XMLoadUInt3(&lhs), XMLoadUInt3(&rhs));
        }

        static inline bool Greater(const Type &lhs, const Type &rhs)
        {
            return XMVector3Greater(XMLoadUInt3(&lhs), XMLoadUInt3(&rhs));
        }

        static inline bool GreaterOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3GreaterOrEqual(XMLoadUInt3(&lhs), XMLoadUInt3(&rhs));
        }

        static inline auto Length(const Type &vec)
        {
            return XMVector3Length(XMLoadUInt3(&vec));
        }

        static inline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector3Less(XMLoadUInt3(&lhs), XMLoadUInt3(&rhs));
        }

        static inline bool LessOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3LessOrEqual(XMLoadUInt3(&lhs), XMLoadUInt3(&rhs));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V3, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3LinePointDistance(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2) std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector3LinePointDistance(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2) XMLoadUInt3(&vec3));
            }
        }

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3NotEqualInt(XMLoadUInt3(&lhs), XMLoadUInt3(&rhs));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Normalize(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector3Normalize(XMLoadUInt3(&vec));
            }
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Orthogonal(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector3Orthogonal(XMLoadUInt3(&vec));
            }
        }

        static inline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector3ReciprocalLength(XMLoadUInt3(&vec));
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Reflect(XMLoadUInt3(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector3Reflect(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3RefractV(XMLoadUInt3(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector3RefractV(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2), XMLoadUInt3(&vec3));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, float index) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector3Refract(XMLoadUInt3(&vec1), std::forward<V2>(vec2), index);
            }
            else if (isSameType) {
                return XMVector3Refract(XMLoadUInt3(&vec1), XMLoadUInt3(&vec2), index);
            }
        }

        template <class M>
        static inline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static inline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), mat);
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<uint32_t, 4>
    {
        typedef ::DirectX::XMUINT4 Type;

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenNormals(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4AngleBetweenNormals(XMLoadUInt4(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector4AngleBetweenNormals(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR AngleBetweenVectors(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4AngleBetweenVectors(XMLoadUInt4(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector4AngleBetweenVectors(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&vec, V2 &&min, V3 &&max) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4ClampLengthV(XMLoadUInt4(&vec), std::forward<V2>(min), std::forward<V3>(max));
            }
            else if (isSameType) {
                return XMVector4ClampLengthV(XMLoadUInt4(&vec), XMLoadUInt4(&min), XMLoadUInt4(&max));
            }
        }

        template <class V>
        static inline XMVECTOR ClampLength(V &&vec, float_t min, float_t max) noexcept
        {
            return XMVector4ClampLength(XMLoadUInt4(&vec), min, max);
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR CrossProduct(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Cross(XMLoadUInt4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector4Cross(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2), XMLoadUInt4(&vec3));
            }
        }

        static inline auto DotProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector4Dot(XMLoadUInt4(&lhs), XMLoadUInt4(&rhs));
        }

        static inline bool Equal(const Type &lhs, const Type &rhs)
        {
            return XMVector2EqualInt(XMLoadUInt4(&lhs), XMLoadUInt4(&rhs));
        }

        static inline bool Greater(const Type &lhs, const Type &rhs)
        {
            return XMVector2Greater(XMLoadUInt4(&lhs), XMLoadUInt4(&rhs));
        }

        static inline bool GreaterOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4GreaterOrEqual(XMLoadUInt4(&lhs), XMLoadUInt4(&rhs));
        }

        static inline auto Length(const Type &vec)
        {
            return XMVector4Length(XMLoadUInt4(&vec));
        }

        static inline bool Less(const Type &lhs, const Type &rhs)
        {
            return XMVector4Less(XMLoadUInt4(&lhs), XMLoadUInt4(&rhs));
        }

        static inline bool LessOrEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4LessOrEqual(XMLoadUInt4(&lhs), XMLoadUInt4(&rhs));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V3, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4LinePointDistance(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2) std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector4LinePointDistance(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2) XMLoadUInt4(&vec3));
            }
        }

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4NotEqualInt(XMLoadUInt4(&lhs), XMLoadUInt4(&rhs));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Normalize(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector4Normalize(XMLoadUInt4(&vec));
            }
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&vec) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Orthogonal(std::forward<V>(vec));
            }
            else if (isSameType) {
                return XMVector4Orthogonal(XMLoadUInt4(&vec));
            }
        }

        static inline XMVECTOR ReciprocalLength(const Type &vec) noexcept
        {
            return XMVector4ReciprocalLength(XMLoadUInt4(&vec));
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&vec1, V2 &&vec2) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Reflect(XMLoadUInt4(&vec1), std::forward<V2>(vec2));
            }
            else if (isSameType) {
                return XMVector4Reflect(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2));
            }
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, V3 &&vec3) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4RefractV(XMLoadUInt4(&vec1), std::forward<V2>(vec2), std::forward<V3>(vec3));
            }
            else if (isSameType) {
                return XMVector4RefractV(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2), XMLoadUInt4(&vec3));
            }
        }

        template <class V1, class V2>
        static inline XMVECTOR Refract(V1 &&vec1, V2 &&vec2, float index) noexcept
        {
            CHECK_ARGUMENT_TYPE_2(V2, isSameType, Type, isXMVector, XMVECTOR);

            if constexpr (isXMVector) {
                return XMVector4Refract(XMLoadUInt4(&vec1), std::forward<V2>(vec2), index);
            }
            else if (isSameType) {
                return XMVector4Refract(XMLoadUInt4(&vec1), XMLoadUInt4(&vec2), index);
            }
        }

        template <class M>
        static inline XMVECTOR Transform(const Type &vec, const M &mat);

        template <>
        static inline XMVECTOR Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector4Transform(XMLoadUInt4(&vec), mat);
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector4Transform(XMLoadUInt4(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline XMVECTOR Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector4Transform(XMLoadUInt4(&vec), XMLoadFloat4x4(&mat));
        }
    };
}

template <class T, int length>
using Vector_Helper_T = typename Vector_Helper<T, length>::Type;

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
            XMStoreSInt2(&result, Vector_Helper<int32_t, 2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMINT3, Matrix>
    {
        static XMINT3 Transform(const XMINT3 &v, const Matrix &m)
        {
            XMINT3 result;
            XMStoreSInt3(&result, Vector_Helper<int32_t, 3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMINT4, Matrix>
    {
        static XMINT4 Transform(const XMINT4 &v, const Matrix &m)
        {
            XMINT4 result;
            XMStoreSInt4(&result, Vector_Helper<int32_t, 4>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMFLOAT2, Matrix>
    {
        static XMFLOAT2 Transform(const XMFLOAT2 &v, const Matrix &m)
        {
            XMFLOAT2 result;
            XMStoreFloat2(&result, Vector_Helper<float_t, 2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMFLOAT3, Matrix>
    {
        static XMFLOAT3 Transform(const XMFLOAT3 &v, const Matrix &m)
        {
            XMFLOAT3 result;
            XMStoreFloat3(&result, Vector_Helper<float_t, 3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMFLOAT4, Matrix>
    {
        static XMFLOAT4 Transform(const XMFLOAT4 &v, const Matrix &m)
        {
            XMFLOAT4 result;
            XMStoreFloat4(&result, Vector_Helper<float_t, 4>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMUINT2, Matrix>
    {
        static XMUINT2 Transform(const XMUINT2 &v, const Matrix &m)
        {
            XMUINT2 result;
            XMStoreUInt2(&result, Vector_Helper<uint32_t, 2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMUINT3, Matrix>
    {
        static XMUINT3 Transform(const XMUINT3 &v, const Matrix &m)
        {
            XMUINT3 result;
            XMStoreUInt3(&result, Vector_Helper<uint32_t, 3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMUINT4, Matrix>
    {
        static auto Transform(const XMUINT4 &v, const Matrix &m)
        {
            XMUINT4 result;
            XMStoreUInt4(&result, Vector_Helper<uint32_t, 4>::Transform(v,m));
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
        static inline bool Less(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::Less(v1,v2);
        }

        static inline bool LessOrEqual(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::LessOrEqual(v1,v2);
        }

        static inline bool Greater(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::Greater(v1,v2);
        }

        static inline bool GreaterOrEqual(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::GreaterOrEqual(v1,v2);
        }

        static inline bool Equal(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::Equal(v1,v2);
        }

        static inline bool NotEqual(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::NotEqual(v1,v2);
        }
    };

    template <>
    struct Vector_Comparator<XMINT3>
    {
        static inline bool Less(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::Less(v1,v2);
        }

        static inline bool LessOrEqual(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::LessOrEqual(v1,v2);
        }

        static inline bool Greater(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::Greater(v1,v2);
        }

        static inline bool GreaterOrEqual(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::GreaterOrEqual(v1,v2);
        }

        static inline bool Equal(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::Equal(v1,v2);
        }

        static inline bool NotEqual(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::NotEqual(v1,v2);
        }
    };

    template <>
    struct Vector_Comparator<XMINT4>
    {
        static inline bool Less(const XMINT4 &v1, const XMINT4 &v2)
        {
            return Vector_Helper<int32_t,4>::Less(v1,v2);
        }

        static inline bool LessOrEqual(const XMINT4 &v1, const XMINT4 &v2)
        {
            return Vector_Helper<int32_t,4>::LessOrEqual(v1,v2);
        }

        static inline bool Greater(const XMINT4 &v1, const XMINT4 &v2)
        {
            return Vector_Helper<int32_t,4>::Greater(v1,v2);
        }

        static inline bool GreaterOrEqual(const XMINT4 &v1, const XMINT4 &v2)
        {
            return Vector_Helper<int32_t,4>::GreaterOrEqual(v1,v2);
        }

        static inline bool Equal(const XMINT4 &v1, const XMINT4 &v2)
        {
            return Vector_Helper<int32_t,4>::Equal(v1,v2);
        }

        static inline bool NotEqual(const XMINT4 &v1, const XMINT4 &v2)
        {
            return Vector_Helper<int32_t,4>::NotEqual(v1,v2);
        }
    };

    template <>
    struct Vector_Comparator<XMFLOAT2>
    {
        static inline bool Less(const XMFLOAT2 &v1, const XMFLOAT2 &v2)
        {
            return Vector_Helper<float_t,2>::Less(v1,v2);
        }

        static inline bool LessOrEqual(const XMFLOAT2 &v1, const XMFLOAT2 &v2)
        {
            return Vector_Helper<float_t,2>::LessOrEqual(v1,v2);
        }

        static inline bool Greater(const XMFLOAT2 &v1, const XMFLOAT2 &v2)
        {
            return Vector_Helper<float_t,2>::Greater(v1,v2);
        }

        static inline bool GreaterOrEqual(const XMFLOAT2 &v1, const XMFLOAT2 &v2)
        {
            return Vector_Helper<float_t,2>::GreaterOrEqual(v1,v2);
        }

        static inline bool Equal(const XMFLOAT2 &v1, const XMFLOAT2 &v2)
        {
            return Vector_Helper<float_t,2>::Equal(v1,v2);
        }

        static inline bool NotEqual(const XMFLOAT2 &v1, const XMFLOAT2 &v2)
        {
            return Vector_Helper<float_t,2>::NotEqual(v1,v2);
        }
    };

    template <>
    struct Vector_Comparator<XMFLOAT3>
    {
        static inline bool Less(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::Less(v1,v2);
        }

        static inline bool LessOrEqual(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::LessOrEqual(v1,v2);
        }

        static inline bool Greater(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::Greater(v1,v2);
        }

        static inline bool GreaterOrEqual(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::GreaterOrEqual(v1,v2);
        }

        static inline bool Equal(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::Equal(v1,v2);
        }

        static inline bool NotEqual(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::NotEqual(v1,v2);
        }
    };

    template <>
    struct Vector_Comparator<XMFLOAT4>
    {
        static inline bool Less(const XMFLOAT4 &v1, const XMFLOAT4 &v2)
        {
            return Vector_Helper<float_t,4>::Less(v1,v2);
        }

        static inline bool LessOrEqual(const XMFLOAT4 &v1, const XMFLOAT4 &v2)
        {
            return Vector_Helper<float_t,4>::LessOrEqual(v1,v2);
        }

        static inline bool Greater(const XMFLOAT4 &v1, const XMFLOAT4 &v2)
        {
            return Vector_Helper<float_t,4>::Greater(v1,v2);
        }

        static inline bool GreaterOrEqual(const XMFLOAT4 &v1, const XMFLOAT4 &v2)
        {
            return Vector_Helper<float_t,4>::GreaterOrEqual(v1,v2);
        }

        static inline bool Equal(const XMFLOAT4 &v1, const XMFLOAT4 &v2)
        {
            return Vector_Helper<float_t,4>::Equal(v1,v2);
        }

        static inline bool NotEqual(const XMFLOAT4 &v1, const XMFLOAT4 &v2)
        {
            return Vector_Helper<float_t,4>::NotEqual(v1,v2);
        }
    };

    template <>
    struct Vector_Comparator<XMUINT2>
    {
        static inline bool Less(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::Less(v1,v2);
        }

        static inline bool LessOrEqual(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::LessOrEqual(v1,v2);
        }

        static inline bool Greater(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::Greater(v1,v2);
        }

        static inline bool GreaterOrEqual(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::GreaterOrEqual(v1,v2);
        }

        static inline bool Equal(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::Equal(v1,v2);
        }

        static inline bool NotEqual(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::NotEqual(v1,v2);
        }
    };

    template <>
    struct Vector_Comparator<XMUINT3>
    {
        static inline bool Less(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::Less(v1,v2);
        }

        static inline bool LessOrEqual(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::LessOrEqual(v1,v2);
        }

        static inline bool Greater(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::Greater(v1,v2);
        }

        static inline bool GreaterOrEqual(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::GreaterOrEqual(v1,v2);
        }

        static inline bool Equal(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::Equal(v1,v2);
        }

        static inline bool NotEqual(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::NotEqual(v1,v2);
        }
    };

    template <>
    struct Vector_Comparator<XMUINT4>
    {
        static inline bool Less(const XMUINT4 &v1, const XMUINT4 &v2)
        {
            return Vector_Helper<uint32_t,4>::Less(v1,v2);
        }

        static inline bool LessOrEqual(const XMUINT4 &v1, const XMUINT4 &v2)
        {
            return Vector_Helper<uint32_t,4>::LessOrEqual(v1,v2);
        }

        static inline bool Greater(const XMUINT4 &v1, const XMUINT4 &v2)
        {
            return Vector_Helper<uint32_t,4>::Greater(v1,v2);
        }

        static inline bool GreaterOrEqual(const XMUINT4 &v1, const XMUINT4 &v2)
        {
            return Vector_Helper<uint32_t,4>::GreaterOrEqual(v1,v2);
        }

        static inline bool Equal(const XMUINT4 &v1, const XMUINT4 &v2)
        {
            return Vector_Helper<uint32_t,4>::Equal(v1,v2);
        }

        static inline bool NotEqual(const XMUINT4 &v1, const XMUINT4 &v2)
        {
            return Vector_Helper<uint32_t,4>::NotEqual(v1,v2);
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
        template <class V1, class V2>
        static inline auto AngleBetweenNormals(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<int32_t,2>::AngleBetweenNormals(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2>
        static inline auto AngleBetweenVectors(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<int32_t,2>::AngleBetweenVectors(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<int32_t,2>::ClampLength(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&v1, V2 &&v2)
        {
            return Vector_Helper<int32_t,2>::CrossProduct(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        static inline auto DotProduct(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::DotProduct(v1,v2);
        }

        template <class V>
        static inline XMVECTOR Length(V &&v) noexcept
        {
            return Vector_Helper<int32_t,2>::Length(std::forward<V>(v));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<int32_t,2>::LinePointDistance(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&v) noexcept
        {
            return Vector_Helper<int32_t,2>::Normalize(std::forward<V>(v));
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&v) noexcept
        {
            return Vector_Helper<int32_t,2>::Orthogonal(std::forward<V>(v));
        }

        static inline XMVECTOR ReciprocalLength(const XMINT2 &v) noexcept
        {
            return Vector_Helper<int32_t,2>::ReciprocalLength(v);
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<int32_t,2>::Reflect(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<int32_t,2>::Refract(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMINT3>
    {
        template <class V1, class V2>
        static inline auto AngleBetweenNormals(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<int32_t,3>::AngleBetweenNormals(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2>
        static inline auto AngleBetweenVectors(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<int32_t,3>::AngleBetweenVectors(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<int32_t,3>::ClampLength(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<int32_t,3>::CrossProduct(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        static inline auto DotProduct(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::DotProduct(v1,v2);
        }

        template <class V>
        static inline XMVECTOR Length(V &&v) noexcept
        {
            return Vector_Helper<int32_t,3>::Length(std::forward<V>(v));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<int32_t,3>::LinePointDistance(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&v) noexcept
        {
            return Vector_Helper<int32_t,3>::Normalize(std::forward<V>(v));
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&v) noexcept
        {
            return Vector_Helper<int32_t,3>::Orthogonal(std::forward<V>(v));
        }

        static inline XMVECTOR ReciprocalLength(const XMINT3 &v) noexcept
        {
            return Vector_Helper<int32_t,3>::ReciprocalLength(v);
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<int32_t,3>::Reflect(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<int32_t,3>::Refract(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMINT4>
    {
        template <class V1, class V2>
        static inline auto AngleBetweenNormals(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<int32_t,4>::AngleBetweenNormals(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2>
        static inline auto AngleBetweenVectors(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<int32_t,4>::AngleBetweenVectors(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<int32_t,4>::ClampLength(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR CrossProduct(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<int32_t,4>::CrossProduct(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        static inline auto DotProduct(const XMINT4 &v1, const XMINT4 &v2)
        {
            return Vector_Helper<int32_t,4>::DotProduct(v1,v2);
        }

        template <class V>
        static inline XMVECTOR Length(V &&v) noexcept
        {
            return Vector_Helper<int32_t,4>::Length(std::forward<V>(v));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<int32_t,4>::LinePointDistance(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&v) noexcept
        {
            return Vector_Helper<int32_t,4>::Normalize(std::forward<V>(v));
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&v) noexcept
        {
            return Vector_Helper<int32_t,4>::Orthogonal(std::forward<V>(v));
        }

        static inline XMVECTOR ReciprocalLength(const XMINT4 &v) noexcept
        {
            return Vector_Helper<int32_t,4>::ReciprocalLength(v);
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<int32_t,4>::Reflect(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<int32_t,4>::Refract(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT2>
    {
        template <class V1, class V2>
        static inline auto AngleBetweenNormals(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<float_t,2>::AngleBetweenNormals(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2>
        static inline auto AngleBetweenVectors(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<float_t,2>::AngleBetweenVectors(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<float_t,2>::ClampLength(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&v1, V1 &&v2) noexcept
        {
            return Vector_Helper<float_t,2>::CrossProduct(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        static inline auto DotProduct(const XMFLOAT2 &v1, const XMFLOAT2 &v2)
        {
            return Vector_Helper<float_t,2>::DotProduct(v1, v2);
        }

        template <class V>
        static inline XMVECTOR Length(V &&v) noexcept
        {
            return Vector_Helper<float_t,2>::Length(std::forward<V>(v));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<float_t,2>::LinePointDistance(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&v) noexcept
        {
            return Vector_Helper<float_t,2>::Normalize(std::forward<V>(v));
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&v) noexcept
        {
            return Vector_Helper<float_t,2>::Orthogonal(std::forward<V>(v));
        }

        static inline XMVECTOR ReciprocalLength(const XMFLOAT2 &v) noexcept
        {
            return Vector_Helper<float_t,2>::ReciprocalLength(v);
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<float_t,2>::Reflect(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<float_t,2>::Refract(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT3>
    {
        template <class V1, class V2>
        static inline auto AngleBetweenNormals(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<float_t,3>::AngleBetweenNormals(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2>
        static inline auto AngleBetweenVectors(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<float_t,3>::AngleBetweenVectors(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<float_t,3>::ClampLength(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<float_t,3>::CrossProduct(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        static inline auto DotProduct(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::DotProduct(v1,v2);
        }

        template <class V>
        static inline XMVECTOR Length(V &&v) noexcept
        {
            return Vector_Helper<float_t,3>::Length(std::forward<V>(v));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<float_t,3>::LinePointDistance(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&v) noexcept
        {
            return Vector_Helper<float_t,3>::Normalize(std::forward<V>(v));
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&v) noexcept
        {
            return Vector_Helper<float_t,3>::Orthogonal(std::forward<V>(v));
        }

        static inline XMVECTOR ReciprocalLength(const XMFLOAT3 &v) noexcept
        {
            return Vector_Helper<float_t,3>::ReciprocalLength(v);
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<float_t,3>::Reflect(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<float_t,3>::Refract(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT4>
    {
        template <class V1, class V2>
        static inline auto AngleBetweenNormals(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<float_t,4>::AngleBetweenNormals(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2>
        static inline auto AngleBetweenVectors(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<float_t,4>::AngleBetweenVectors(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<float_t,4>::ClampLength(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR CrossProduct(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<float_t,4>::CrossProduct(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        static inline auto DotProduct(const XMFLOAT4 &v1, const XMFLOAT4 &v2)
        {
            return Vector_Helper<float_t,4>::DotProduct(v1,v2);
        }

        template <class V>
        static inline XMVECTOR Length(V &&v) noexcept
        {
            return Vector_Helper<float_t,4>::Length(std::forward<V>(v));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<float_t,4>::LinePointDistance(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&v) noexcept
        {
            return Vector_Helper<float_t,4>::Normalize(std::forward<V>(v));
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&v) noexcept
        {
            return Vector_Helper<float_t,4>::Orthogonal(std::forward<V>(v));
        }

        static inline XMVECTOR ReciprocalLength(const XMFLOAT4 &v) noexcept
        {
            return Vector_Helper<float_t,4>::ReciprocalLength(v);
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<float_t,4>::Reflect(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<float_t,4>::Refract(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMUINT2>
    {
        template <class V1, class V2>
        static inline auto AngleBetweenNormals(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,2>::AngleBetweenNormals(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2>
        static inline auto AngleBetweenVectors(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,2>::AngleBetweenVectors(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<uint32_t,2>::ClampLength(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,2>::CrossProduct(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        static inline auto DotProduct(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::DotProduct(v1,v2);
        }

        template <class V>
        static inline XMVECTOR Length(V &&v) noexcept
        {
            return Vector_Helper<uint32_t,2>::Length(std::forward<V>(v));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<uint32_t,2>::LinePointDistance(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&v) noexcept
        {
            return Vector_Helper<uint32_t,2>::Normalize(std::forward<V>(v));
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&v) noexcept
        {
            return Vector_Helper<uint32_t,2>::Orthogonal(std::forward<V>(v));
        }

        static inline XMVECTOR ReciprocalLength(const XMUINT2 &v) noexcept
        {
            return Vector_Helper<uint32_t,2>::ReciprocalLength(v);
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,2>::Reflect(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<uint32_t,2>::Refract(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMUINT3>
    {
        template <class V1, class V2>
        static inline auto AngleBetweenNormals(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,3>::AngleBetweenNormals(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2>
        static inline auto AngleBetweenVectors(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,3>::AngleBetweenVectors(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<uint32_t,3>::ClampLength(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        template <class V1, class V2>
        static inline XMVECTOR CrossProduct(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,3>::CrossProduct(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        static inline auto DotProduct(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::DotProduct(v1,v2);
        }

        template <class V>
        static inline XMVECTOR Length(V &&v) noexcept
        {
            return Vector_Helper<uint32_t,3>::Length(std::forward<V>(v));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<uint32_t,3>::LinePointDistance(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&v) noexcept
        {
            return Vector_Helper<uint32_t,3>::Normalize(std::forward<V>(v));
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&v) noexcept
        {
            return Vector_Helper<uint32_t,3>::Orthogonal(std::forward<V>(v));
        }

        static inline XMVECTOR ReciprocalLength(const XMUINT3 &v) noexcept
        {
            return Vector_Helper<uint32_t,3>::ReciprocalLength(v);
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,3>::Reflect(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<uint32_t,3>::Refract(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };

    template <>
    struct Vector_Geometry<XMUINT4>
    {
        template <class V1, class V2>
        static inline auto AngleBetweenNormals(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,4>::AngleBetweenNormals(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2>
        static inline auto AngleBetweenVectors(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,4>::AngleBetweenVectors(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR ClampLength(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<uint32_t,4>::ClampLength(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR CrossProduct(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<uint32_t,4>::CrossProduct(
                std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3)
            );
        }

        static inline auto DotProduct(const XMUINT4 &v1, const XMUINT4 &v2)
        {
            return Vector_Helper<uint32_t,4>::DotProduct(v1,v2);
        }

        template <class V>
        static inline XMVECTOR Length(V &&v) noexcept
        {
            return Vector_Helper<uint32_t,4>::Length(std::forward<V>(v));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR LinePointDistance(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<uint32_t,4>::LinePointDistance(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }

        template <class V>
        static inline XMVECTOR Normalize(V &&v) noexcept
        {
            return Vector_Helper<uint32_t,4>::Normalize(std::forward<V>(v));
        }

        template <class V>
        static inline XMVECTOR Orthogonal(V &&v) noexcept
        {
            return Vector_Helper<uint32_t,4>::Orthogonal(std::forward<V>(v));
        }

        static inline XMVECTOR ReciprocalLength(const XMUINT4 &v) noexcept
        {
            return Vector_Helper<uint32_t,4>::ReciprocalLength(v);
        }

        template <class V1, class V2>
        static inline XMVECTOR Reflect(V1 &&v1, V2 &&v2) noexcept
        {
            return Vector_Helper<uint32_t,4>::Reflect(std::forward<V1>(v1), std::forward<V2>(v2));
        }

        template <class V1, class V2, class V3>
        static inline XMVECTOR Refract(V1 &&v1, V2 &&v2, V3 &&v3) noexcept
        {
            return Vector_Helper<uint32_t,4>::Refract(std::forward<V1>(v1), std::forward<V2>(v2), std::forward<V3>(v3));
        }
    };
}

template <class V>
inline bool operator<(const V &vector1, const V &vector2)
{
    return Vector_Comparator<V>::Less(vector1, vector2);
}

template <class V>
inline bool operator<=(const V &vector1, const V &vector2)
{
    return Vector_Comparator<V>::LessOrEqual(vector1, vector2);
}

template <class V>
inline bool operator>(const V &vector1, const V &vector2)
{
    return Vector_Comparator<V>::Greater(vector1, vector2);
}

template <class V>
inline bool operator>=(const V &vector1, const V &vector2)
{
    return Vector_Comparator<V>::GreaterOrEqual(vector1, vector2);
}

template <class V>
inline bool operator==(const V &vector1, const V &vector2)
{
    return Vector_Comparator<V>::Equal(vector1, vector2);
}

template <class V>
inline bool operator!=(const V &vector1, const V &vector2)
{
    return Vector_Comparator<V>::NotEqual(vector1, vector2);
}

namespace VectorAngle
{
    /// <summary>Computes the radian angle between two 2-, 3- or 4D vectors.</summary>
    template <class V1, class V2>
    inline auto Angle(V1 &&vector1, V2 &&vector2) noexcept
    {
        return Vector_Geometry<std::decay_t<V1>>::AngleBetweenVectors(std::forward<V1>(vector1), std::forward<V2>(vector2));
    }

    /// <summary>Computes the radian angle between two normalized 2-, 3- or 4D vectors.</summary>
    template <class V1, class V2>
    inline auto OrientedAngle(V1 &&vector1, V2 &&vector2) noexcept
    {
        return Vector_Geometry<std::decay_t<V1>>::AngleBetweenNormals(std::forward<V1>(vector1), std::forward<V2>(vector2));
    }
}

/// <summary> Clamps the length of a 2-, 3- or 4D vector to a given range.</summary>
template <class V1, class V2, class V3>
inline XMVECTOR ClampLength(V1 &&vector, V2 &&lengthMin, V3 &&lengthMax) noexcept
{
    return Vector_Geometry<std::decay_t<V1>>::ClampLength(
        std::forward<V1>(vector), std::forward<V2>(lengthMin), std::forward<V3>(lengthMax)
    );
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

/// <summary>Computes the dot product between a 2-, 3- or 4D vector.</summary>
template <class V>
inline XMVECTOR DotProduct(const V &vector1, const V &vector2)
{
    return Vector_Geometry<V>::DotProduct(vector1, vector2);
}

/// <summary>Computes the length of a 2-, 3- or 4D vector.</summary>
template <class V>
inline XMVECTOR Length(V&& vector) noexcept
{
    return Vector_Geometry<std::decay_t<V>>::Length(std::forward<V>(vector));
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
    return Vector_Geometry<std::decay_t<V>>::Orthogonal(std::forward<V>(v));
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
