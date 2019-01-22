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
