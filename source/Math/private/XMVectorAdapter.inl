namespace
{
    using namespace DirectX;

    template <class T, int length>
    struct Vector_Helper;

    template <>
    struct Vector_Helper<int32_t, 2>
    {
        using Type = ::DirectX::XMINT2;

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
        using Type = ::DirectX::XMINT3;

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
        using Type = ::DirectX::XMINT4;

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
        using Type = ::DirectX::XMFLOAT2;

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
        using Type = ::DirectX::XMFLOAT3;

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
            return XMVector4Transform(XMLoadFloat3(&vec), mat);
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
        using Type = ::DirectX::XMFLOAT4;

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
        using Type = ::DirectX::XMUINT2;

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
        using Type = ::DirectX::XMUINT3;

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
        using Type = ::DirectX::XMUINT4;

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
