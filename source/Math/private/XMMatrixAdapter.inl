namespace
{
    using namespace DirectX;

    template <class T, int rows, int columns>
    struct Matrix_Helper;

    template <class T>
    struct Matrix_Helper<T, 3, 3>
    {
        typedef ::DirectX::XMFLOAT3X3 Type;
    };

    template <class T>
    struct Matrix_Helper<T, 3, 4>
    {
        typedef ::DirectX::XMFLOAT3X4 Type;
    };

    template <class T>
    struct Matrix_Helper<T, 4, 3>
    {
        typedef ::DirectX::XMFLOAT4X3 Type;
    };

    template <class T>
    struct Matrix_Helper<T, 4, 4>
    {
        typedef ::DirectX::XMFLOAT4X4 Type;
    };
}

template <class T, int rows, int columns>
using Matrix_Helper_T = typename Matrix_Helper<T, rows, columns>::Type;
