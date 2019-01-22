namespace
{
    template <class V>
    struct Vector_Geometry;

    template <>
    struct Vector_Geometry<XMINT2>
    {
        static inline auto DotProduct(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::DotProduct(v1,v2);
        }

        static inline auto CrossProduct(const XMINT2 &v1, const XMINT2 &v2)
        {
            return Vector_Helper<int32_t,2>::CrossProduct(v1,v2);
        }
    };

    template <>
    struct Vector_Geometry<XMINT3>
    {
        static inline auto DotProduct(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::DotProduct(v1,v2);
        }

        static inline auto CrossProduct(const XMINT3 &v1, const XMINT3 &v2)
        {
            return Vector_Helper<int32_t,3>::CrossProduct(v1,v2);
        }
    };

    template <>
    struct Vector_Geometry<XMINT4>
    {
        static inline auto DotProduct(const XMINT4 &v1, const XMINT4 &v2)
        {
            return Vector_Helper<int32_t,4>::DotProduct(v1,v2);
        }

        static inline auto CrossProduct(const XMINT4 &v1, const XMINT4 &v2, const XMINT4 &v3)
        {
            return Vector_Helper<int32_t,4>::CrossProduct(v1,v2,v3);
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT3>
    {
        static inline auto DotProduct(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::DotProduct(v1,v2);
        }

        static inline auto CrossProduct(const XMFLOAT3 &v1, const XMFLOAT3 &v2)
        {
            return Vector_Helper<float_t,3>::CrossProduct(v1,v2);
        }
    };

    template <>
    struct Vector_Geometry<XMFLOAT4>
    {
        static inline auto DotProduct(const XMFLOAT4 &v1, const XMFLOAT4 &v2)
        {
            return Vector_Helper<float_t,4>::DotProduct(v1,v2);
        }

        static inline auto CrossProduct(const XMFLOAT4 &v1, const XMFLOAT4 &v2, const XMFLOAT4 &v3)
        {
            return Vector_Helper<float_t,4>::CrossProduct(v1,v2,v3);
        }
    };

    template <>
    struct Vector_Geometry<XMUINT2>
    {
        static inline auto DotProduct(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::DotProduct(v1,v2);
        }

        static inline auto CrossProduct(const XMUINT2 &v1, const XMUINT2 &v2)
        {
            return Vector_Helper<uint32_t,2>::CrossProduct(v1,v2);
        }
    };

    template <>
    struct Vector_Geometry<XMUINT3>
    {
        static inline auto DotProduct(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::DotProduct(v1,v2);
        }

        static inline auto CrossProduct(const XMUINT3 &v1, const XMUINT3 &v2)
        {
            return Vector_Helper<uint32_t,3>::CrossProduct(v1,v2);
        }
    };

    template <>
    struct Vector_Geometry<XMUINT4>
    {
        static inline auto DotProduct(const XMUINT4 &v1, const XMUINT4 &v2)
        {
            return Vector_Helper<uint32_t,4>::DotProduct(v1,v2);
        }

        static inline auto CrossProduct(const XMUINT4 &v1, const XMUINT4 &v2, const XMUINT4 &v3)
        {
            return Vector_Helper<uint32_t,4>::CrossProduct(v1,v2,v3);
        }
    };
}
