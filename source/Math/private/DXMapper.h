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

namespace
{
    using namespace DirectX;

    template <class T, int length>
    struct Vector_Helper;

    template <>
    struct Vector_Helper<int32_t, 2>
    {
        typedef ::DirectX::XMINT2 Type;

        template <class L>
        static inline auto ClampLength(const Type &vec, L min, L max);

        template <>
        static inline auto ClampLength<float>(const Type &vec, float min, float max)
        {
            return XMVector2ClampLength(XMLoadSInt2(&vec), min, max);
        }

        template <>
        static inline auto ClampLength<XMINT2>(const Type &vec, XMINT2 min, XMINT2 max)
        {
            return XMVector2ClampLengthV(XMLoadSInt2(&vec), XMLoadSInt2(&min), XMLoadSInt2(&max));
        }

        template <>
        static inline auto ClampLength<XMVECTOR>(const Type &vec, XMVECTOR min, XMVECTOR max)
        {
            return XMVector2ClampLengthV(XMLoadSInt2(&vec), min, max);
        }

        static inline auto CrossProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector2Cross(XMLoadSInt2(&lhs), XMLoadSInt2(&rhs));
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

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2NotEqualInt(XMLoadSInt2(&lhs), XMLoadSInt2(&rhs));
        }

        template <class M>
        static inline auto Transform(const Type &vec, const M &mat);

        template <>
        static inline auto Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), mat);
        }

        template <>
        static inline auto Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector2Transform(XMLoadSInt2(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<int32_t, 3>
    {
        typedef ::DirectX::XMINT3 Type;

        template <class L>
        static inline auto ClampLength(const Type &vec, L min, L max);

        template <>
        static inline auto ClampLength<float>(const Type &vec, float min, float max)
        {
            return XMVector3ClampLength(XMLoadSInt3(&vec), min, max);
        }

        template <>
        static inline auto ClampLength<XMINT3>(const Type &vec, XMINT3 min, XMINT3 max)
        {
            return XMVector3ClampLengthV(XMLoadSInt3(&vec), XMLoadSInt3(&min), XMLoadSInt3(&max));
        }

        template <>
        static inline auto ClampLength<XMVECTOR>(const Type &vec, XMVECTOR min, XMVECTOR max)
        {
            return XMVector3ClampLengthV(XMLoadSInt3(&vec), min, max);
        }

        static inline auto CrossProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector3Cross(XMLoadSInt3(&lhs), XMLoadSInt3(&rhs));
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

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3NotEqualInt(XMLoadSInt3(&lhs), XMLoadSInt3(&rhs));
        }

        template <class M>
        static inline auto Transform(const Type &vec, const M &mat);

        template <>
        static inline auto Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), mat);
        }

        template <>
        static inline auto Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            using namespace DirectX;
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            using namespace DirectX;
            return XMVector3Transform(XMLoadSInt3(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<int32_t, 4>
    {
        typedef ::DirectX::XMINT4 Type;

        template <class L>
        static inline auto ClampLength(const Type &vec, L min, L max);

        template <>
        static inline auto ClampLength<float>(const Type &vec, float min, float max)
        {
            return XMVector4ClampLength(XMLoadSInt4(&vec), min, max);
        }

        template <>
        static inline auto ClampLength<XMINT4>(const Type &vec, XMINT4 min, XMINT4 max)
        {
            return XMVector4ClampLengthV(XMLoadSInt4(&vec), XMLoadSInt4(&min), XMLoadSInt4(&max));
        }

        template <>
        static inline auto ClampLength<XMVECTOR>(const Type &vec, XMVECTOR min, XMVECTOR max)
        {
            return XMVector4ClampLengthV(XMLoadSInt4(&vec), min, max);
        }

        template <class ... T>
        static inline auto CrossProduct(const Type &lhs, T&&... rhs)
        {
            return XMVector4Cross(XMLoadSInt4(&lhs), XMLoadSInt4(&rhs)...);
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

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4NotEqualInt(XMLoadSInt4(&lhs), XMLoadSInt4(&rhs));
        }

        template <class M>
        static inline auto Transform(const Type &vec, const M &mat);

        template <>
        static inline auto Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector4Transform(XMLoadSInt4(&vec), mat);
        }

        template <>
        static inline auto Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector4Transform(XMLoadSInt4(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector4Transform(XMLoadSInt4(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<float_t, 2>
    {
        typedef ::DirectX::XMFLOAT2 Type;

        template <class L>
        static inline auto ClampLength(const Type &vec, L min, L max);

        template <>
        static inline auto ClampLength<float>(const Type &vec, float min, float max)
        {
            return XMVector2ClampLength(XMLoadFloat2(&vec), min, max);
        }

        template <>
        static inline auto ClampLength<XMFLOAT2>(const Type &vec, XMFLOAT2 min, XMFLOAT2 max)
        {
            return XMVector2ClampLengthV(XMLoadFloat2(&vec), XMLoadFloat2(&min), XMLoadFloat2(&max));
        }

        template <>
        static inline auto ClampLength<XMVECTOR>(const Type &vec, XMVECTOR min, XMVECTOR max)
        {
            return XMVector2ClampLengthV(XMLoadFloat2(&vec), min, max);
        }

        static inline auto CrossProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector2Cross(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs));
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

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2NotEqual(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs));
        }

        template <class M>
        static inline auto Transform(const Type &vec, const M &mat);

        template <>
        static inline auto Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), mat);
        }

        template <>
        static inline auto Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector2Transform(XMLoadFloat2(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<float_t, 3>
    {
        typedef ::DirectX::XMFLOAT3 Type;

        template <class L>
        static inline auto ClampLength(const Type &vec, L min, L max);

        template <>
        static inline auto ClampLength<float>(const Type &vec, float min, float max)
        {
            return XMVector3ClampLength(XMLoadFloat3(&vec), min, max);
        }

        template <>
        static inline auto ClampLength<XMFLOAT3>(const Type &vec, XMFLOAT3 min, XMFLOAT3 max)
        {
            return XMVector3ClampLengthV(XMLoadFloat3(&vec), XMLoadFloat3(&min), XMLoadFloat3(&max));
        }

        template <>
        static inline auto ClampLength<XMVECTOR>(const Type &vec, XMVECTOR min, XMVECTOR max)
        {
            return XMVector3ClampLengthV(XMLoadFloat3(&vec), min, max);
        }

        static inline auto CrossProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector3Cross(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs));
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

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3NotEqual(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs));
        }

        template <class M>
        static inline auto Transform(const Type &vec, const M &mat);

        template <>
        static inline auto Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), mat);
        }

        template <>
        static inline auto Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector3Transform(XMLoadFloat3(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<float, 4>
    {
        typedef ::DirectX::XMFLOAT4 Type;

        template <class L>
        static inline auto ClampLength(const Type &vec, L min, L max);

        template <>
        static inline auto ClampLength<float>(const Type &vec, float min, float max)
        {
            return XMVector4ClampLength(XMLoadFloat4(&vec), min, max);
        }

        template <>
        static inline auto ClampLength<XMFLOAT4>(const Type &vec, XMFLOAT4 min, XMFLOAT4 max)
        {
            return XMVector4ClampLengthV(XMLoadFloat4(&vec), XMLoadFloat4(&min), XMLoadFloat4(&max));
        }

        template <>
        static inline auto ClampLength<XMVECTOR>(const Type &vec, XMVECTOR min, XMVECTOR max)
        {
            return XMVector4ClampLengthV(XMLoadFloat4(&vec), min, max);
        }

        template <class ... T>
        static inline auto CrossProduct(const Type &lhs, T&&... rhs)
        {
            return XMVector4Cross(XMLoadFloat4(&lhs), XMLoadFloat4(&rhs)...);
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

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4NotEqual(XMLoadFloat4(&lhs), XMLoadFloat4(&rhs));
        }

        template <class M>
        static inline auto Transform(const Type &vec, const M &mat);

        template <>
        static inline auto Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector4Transform(XMLoadFloat4(&vec), mat);
        }

        template <>
        static inline auto Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector4Transform(XMLoadFloat4(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector4Transform(XMLoadFloat4(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<uint32_t, 2>
    {
        typedef ::DirectX::XMUINT2 Type;

        template <class L>
        static inline auto ClampLength(const Type &vec, L min, L max);

        template <>
        static inline auto ClampLength<float>(const Type &vec, float min, float max)
        {
            return XMVector2ClampLength(XMLoadUInt2(&vec), min, max);
        }

        template <>
        static inline auto ClampLength<XMUINT2>(const Type &vec, XMUINT2 min, XMUINT2 max)
        {
            return XMVector2ClampLengthV(XMLoadUInt2(&vec), XMLoadUInt2(&min), XMLoadUInt2(&max));
        }

        template <>
        static inline auto ClampLength<XMVECTOR>(const Type &vec, XMVECTOR min, XMVECTOR max)
        {
            return XMVector2ClampLengthV(XMLoadUInt2(&vec), min, max);
        }

        static inline auto CrossProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector2Cross(XMLoadUInt2(&lhs), XMLoadUInt2(&rhs));
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

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector2NotEqualInt(XMLoadUInt2(&lhs), XMLoadUInt2(&rhs));
        }

        template <class M>
        static inline auto Transform(const Type &vec, const M &mat);

        template <>
        static inline auto Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), mat);
        }

        template <>
        static inline auto Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector2Transform(XMLoadUInt2(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<uint32_t, 3>
    {
        typedef ::DirectX::XMUINT3 Type;

        template <class L>
        static inline auto ClampLength(const Type &vec, L min, L max);

        template <>
        static inline auto ClampLength<float>(const Type &vec, float min, float max)
        {
            return XMVector3ClampLength(XMLoadUInt3(&vec), min, max);
        }

        template <>
        static inline auto ClampLength<XMUINT3>(const Type &vec, XMUINT3 min, XMUINT3 max)
        {
            return XMVector3ClampLengthV(XMLoadUInt3(&vec), XMLoadUInt3(&min), XMLoadUInt3(&max));
        }

        template <>
        static inline auto ClampLength<XMVECTOR>(const Type &vec, XMVECTOR min, XMVECTOR max)
        {
            return XMVector3ClampLengthV(XMLoadUInt3(&vec), min, max);
        }

        static inline auto CrossProduct(const Type &lhs, const Type &rhs)
        {
            return XMVector3Cross(XMLoadUInt3(&lhs), XMLoadUInt3(&rhs));
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

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector3NotEqualInt(XMLoadUInt3(&lhs), XMLoadUInt3(&rhs));
        }

        template <class M>
        static inline auto Transform(const Type &vec, const M &mat);

        template <>
        static inline auto Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), mat);
        }

        template <>
        static inline auto Transform<XMFLOAT3X3>(const Type &vec, const XMFLOAT3X3 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat3x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X3>(const Type &vec, const XMFLOAT4X3 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat4x3(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
        {
            return XMVector3Transform(XMLoadUInt3(&vec), XMLoadFloat4x4(&mat));
        }
    };

    template <>
    struct Vector_Helper<uint32_t, 4>
    {
        typedef ::DirectX::XMUINT4 Type;

        template <class L>
        static inline auto ClampLength(const Type &vec, L min, L max);

        template <>
        static inline auto ClampLength<float>(const Type &vec, float min, float max)
        {
            return XMVector4ClampLength(XMLoadUInt4(&vec), min, max);
        }

        template <>
        static inline auto ClampLength<XMUINT4>(const Type &vec, XMUINT4 min, XMUINT4 max)
        {
            return XMVector4ClampLengthV(XMLoadUInt4(&vec), XMLoadUInt4(&min), XMLoadUInt4(&max));
        }

        template <>
        static inline auto ClampLength<XMVECTOR>(const Type &vec, XMVECTOR min, XMVECTOR max)
        {
            return XMVector4ClampLengthV(XMLoadUInt4(&vec), min, max);
        }

        template <class ... T>
        static inline auto CrossProduct(const Type &lhs, T&&... rhs)
        {
            return XMVector4Cross(XMLoadUInt4(&lhs), XMLoadUInt4(&rhs)...);
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

        static inline bool NotEqual(const Type &lhs, const Type &rhs)
        {
            return XMVector4NotEqualInt(XMLoadUInt4(&lhs), XMLoadUInt4(&rhs));
        }

        template <class M>
        static inline auto Transform(const Type &vec, const M &mat);

        template <>
        static inline auto Transform<XMMATRIX>(const Type &vec, const XMMATRIX &mat)
        {
            return XMVector4Transform(XMLoadUInt4(&vec), mat);
        }

        template <>
        static inline auto Transform<XMFLOAT3X4>(const Type &vec, const XMFLOAT3X4 &mat)
        {
            return XMVector4Transform(XMLoadUInt4(&vec), XMLoadFloat3x4(&mat));
        }

        template <>
        static inline auto Transform<XMFLOAT4X4>(const Type &vec, const XMFLOAT4X4 &mat)
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
        static auto Transform(const XMINT2 &v, const Matrix &m)
        {
            XMINT2 result;
            XMStoreSInt2(&result, Vector_Helper<int32_t, 2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMINT3, Matrix>
    {
        static auto Transform(const XMINT3 &v, const Matrix &m)
        {
            XMINT3 result;
            XMStoreSInt3(&result, Vector_Helper<int32_t, 3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMINT4, Matrix>
    {
        static auto Transform(const XMINT4 &v, const Matrix &m)
        {
            XMINT4 result;
            XMStoreSInt4(&result, Vector_Helper<int32_t, 4>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMFLOAT2, Matrix>
    {
        static auto Transform(const XMFLOAT2 &v, const Matrix &m)
        {
            XMFLOAT2 result;
            XMStoreFloat2(&result, Vector_Helper<float_t, 2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMFLOAT3, Matrix>
    {
        static auto Transform(const XMFLOAT3 &v, const Matrix &m)
        {
            XMFLOAT3 result;
            XMStoreFloat3(&result, Vector_Helper<float_t, 3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMFLOAT4, Matrix>
    {
        static auto Transform(const XMFLOAT4 &v, const Matrix &m)
        {
            XMFLOAT4 result;
            XMStoreFloat4(&result, Vector_Helper<float_t, 4>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMUINT2, Matrix>
    {
        static auto Transform(const XMUINT2 &v, const Matrix &m)
        {
            XMUINT2 result;
            XMStoreUInt2(&result, Vector_Helper<uint32_t, 2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct TransformMapper<XMUINT3, Matrix>
    {
        static auto Transform(const XMUINT3 &v, const Matrix &m)
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
        template <class L>
        static inline auto ClampLength(const XMINT2 &v1, L&& v2, L&& v3)
        {
            return Vector_Helper<int32_t,2>::ClampLength<L>(v1,v2,v3);
        }

        static inline auto CrossProduct(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::CrossProduct(v1,v2);
        }

        static inline auto DotProduct(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::DotProduct(v1,v2);
        }

        static inline auto Length(const XMINT2 &v)
        {
            return Vector_Helper<int32_t,2>::Length(v);
        }
    };

    template <>
    struct Vector_Geometry<XMINT3>
    {
        template <class L>
        static inline auto ClampLength(const XMINT3 &v1, L&& v2, L&& v3)
        {
            return Vector_Helper<int32_t,3>::ClampLength(v1, std::forward<L>(v2), std::forward<L>(v3));
        }

        static inline auto CrossProduct(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::CrossProduct(v1,v2);
        }

        static inline auto DotProduct(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::DotProduct(v1,v2);
        }

        static inline auto Length(const XMINT3 &v)
        {
            return Vector_Helper<int32_t,3>::Length(v);
        }
    };

    template <>
    struct Vector_Geometry<XMINT4>
    {
        template <class L>
        static inline auto ClampLength(const XMINT4 &v1, L&& v2, L&& v3)
        {
            return Vector_Helper<int32_t,4>::ClampLength(v1, std::forward<L>(v2), std::forward<L>(v3));
        }

        static inline auto CrossProduct(const XMINT4 &v1, const XMINT4 &v2, const XMINT4 &v3)
        {
            return Vector_Helper<int32_t,4>::CrossProduct(v1,v2,v3);
        }

        static inline auto DotProduct(const XMINT4 &v1, const XMINT4 &v2)
        {
            return Vector_Helper<int32_t,4>::DotProduct(v1,v2);
        }

        static inline auto Length(const XMINT4 &v)
        {
            return Vector_Helper<int32_t,4>::Length(v);
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT2>
    {
        template <class L>
        static inline auto ClampLength(const XMFLOAT2 &v1, L&& v2, L&& v3)
        {
            return Vector_Helper<float_t,2>::ClampLength(v1, std::forward(v2), std::forward(v3));;
        }

        static inline auto CrossProduct(const XMFLOAT2 &v1, const XMFLOAT2 &v2)
        {
            return Vector_Helper<float_t,2>::CrossProduct(v1,v2);
        }

        static inline auto DotProduct(const XMFLOAT2 &v1, const XMFLOAT2 &v2)
        {
            return Vector_Helper<float_t,2>::DotProduct(v1, v2);
        }

        static inline auto Length(const XMFLOAT2 &v)
        {
            return Vector_Helper<float_t,2>::Length(v);
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT3>
    {
        template <class L>
        static inline auto ClampLength(const XMFLOAT3 &v1, L&& v2, L&& v3)
        {
            return Vector_Helper<float_t,3>::ClampLength(v1, std::forward(v2), std::forward(v3));;
        }

        static inline auto CrossProduct(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::CrossProduct(v1,v2);
        }

        static inline auto DotProduct(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::DotProduct(v1,v2);
        }

        static inline auto Length(const XMFLOAT3 &v)
        {
            return Vector_Helper<float_t,3>::Length(v);
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT4>
    {
        template <class L>
        static inline auto ClampLength(const XMFLOAT4 &v1, L&& v2, L&& v3)
        {
            return Vector_Helper<float_t,4>::ClampLength(v1, std::forward(v2), std::forward(v3));
        }

        static inline auto CrossProduct(const XMFLOAT4 &v1, const XMFLOAT4 &v2, const XMFLOAT4 &v3)
        {
            return Vector_Helper<float_t,4>::CrossProduct(v1,v2,v3);
        }

        static inline auto DotProduct(const XMFLOAT4 &v1, const XMFLOAT4 &v2)
        {
            return Vector_Helper<float_t,4>::DotProduct(v1,v2);
        }

        static inline auto Length(const XMFLOAT4 &v)
        {
            return Vector_Helper<float_t,4>::Length(v);
        }
    };

    template <>
    struct Vector_Geometry<XMUINT2>
    {
        template <class L>
        static inline auto ClampLength(const XMUINT2 &v1, L&& v2, L&& v3)
        {
            return Vector_Helper<uint32_t,2>::ClampLength(v1, std::forward(v2), std::forward(v3));
        }

        static inline auto CrossProduct(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::CrossProduct(v1,v2);
        }

        static inline auto DotProduct(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::DotProduct(v1,v2);
        }

        static inline auto Length(const XMUINT2 &v)
        {
            return Vector_Helper<uint32_t,2>::Length(v);
        }
    };

    template <>
    struct Vector_Geometry<XMUINT3>
    {
        template <class L>
        static inline auto ClampLength(const XMUINT3 &v1, L&& v2, L&& v3)
        {
            return Vector_Helper<uint32_t,3>::ClampLength(v1, std::forward(v2), std::forward(v3));
        }

        static inline auto CrossProduct(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::CrossProduct(v1,v2);
        }

        static inline auto DotProduct(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::DotProduct(v1,v2);
        }

        static inline auto Length(const XMUINT3 &v)
        {
            return Vector_Helper<uint32_t,3>::Length(v);
        }
    };

    template <>
    struct Vector_Geometry<XMUINT4>
    {
        template <class L>
        static inline auto ClampLength(const XMUINT4 &v1, L&& v2, L&& v3)
        {
            return Vector_Helper<uint32_t,4>::ClampLength(v1, std::forward(v2), std::forward(v3));
        }

        static inline auto CrossProduct(const XMUINT4 &v1, const XMUINT4 &v2, const XMUINT4 &v3)
        {
            return Vector_Helper<uint32_t,4>::CrossProduct(v1,v2,v3);
        }

        static inline auto DotProduct(const XMUINT4 &v1, const XMUINT4 &v2)
        {
            return Vector_Helper<uint32_t,4>::DotProduct(v1,v2);
        }

        static inline auto Length(const XMUINT4 &v)
        {
            return Vector_Helper<uint32_t,4>::Length(v);
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

template <class V, class L>
inline auto clampLength(const V &vector, L&& lengthMin, L&& lengthMax)
{
    return Vector_Geometry<V>::ClampLength(vector, std::forward<L>(lengthMin), std::forward<L>(lengthMax));
}

template <class V>
inline auto crossProduct(const V &vector1, const V &vector2)
{
    return Vector_Geometry<V>::CrossProduct(vector1, vector2);
}

template <class V>
inline auto dotProduct(const V &vector1, const V &vector2)
{
    return Vector_Geometry<V>::DotProduct(vector1, vector2);
}

template <class V>
inline auto length(const V &vector)
{
    return Vector_Geometry<V>::Length(v);
}

template <class V>
inline auto magnitude(const V &vector)
{
    return Vector_Geometry<V>::Length(v);
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
