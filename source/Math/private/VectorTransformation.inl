namespace
{
    using namespace DirectX;

    template <class Vector, class Matrix>
    struct Vector_Transformer;

    template <class Matrix>
    struct Vector_Transformer<XMINT2, Matrix>
    {
        static auto Transform(const XMINT2 &v, const Matrix &m)
        {
            XMINT2 result;
            XMStoreSInt2(&result, Vector_Helper<int32_t,2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct Vector_Transformer<XMINT3, Matrix>
    {
        static auto Transform(const XMINT3 &v, const Matrix &m)
        {
            XMINT3 result;
            XMStoreSInt3(&result, Vector_Helper<int32_t,3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct Vector_Transformer<XMINT4, Matrix>
    {
        static auto Transform(const XMINT4 &v, const Matrix &m)
        {
            XMINT4 result;
            XMStoreSInt4(&result, Vector_Helper<int32_t,4>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct Vector_Transformer<XMFLOAT2, Matrix>
    {
        static auto Transform(const XMFLOAT2 &v, const Matrix &m)
        {
            XMFLOAT2 result;
            XMStoreFloat2(&result, Vector_Helper<float_t,2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct Vector_Transformer<XMFLOAT3, Matrix>
    {
        static auto Transform(const XMFLOAT3 &v, const Matrix &m)
        {
            XMFLOAT3 result;
            XMStoreFloat3(&result, Vector_Helper<float_t,3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct Vector_Transformer<XMFLOAT4, Matrix>
    {
        static auto Transform(const XMFLOAT4 &v, const Matrix &m)
        {
            XMFLOAT4 result;
            XMStoreFloat4(&result, Vector_Helper<float_t,4>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct Vector_Transformer<XMUINT2, Matrix>
    {
        static auto Transform(const XMUINT2 &v, const Matrix &m)
        {
            XMUINT2 result;
            XMStoreUInt2(&result, Vector_Helper<uint32_t,2>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct Vector_Transformer<XMUINT3, Matrix>
    {
        static auto Transform(const XMUINT3 &v, const Matrix &m)
        {
            XMUINT3 result;
            XMStoreUInt3(&result, Vector_Helper<uint32_t,3>::Transform(v,m));
            return result;
        }
    };

    template <class Matrix>
    struct Vector_Transformer<XMUINT4, Matrix>
    {
        static auto Transform(const XMUINT4 &v, const Matrix &m)
        {
            XMUINT4 result;
            XMStoreUInt4(&result, Vector_Helper<uint32_t,4>::Transform(v,m));
            return result;
        }
    };
}
