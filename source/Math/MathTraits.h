#pragma once

#include <DirectXMath.h>

#ifndef _MSC_VER

namespace std
{
    template<class T, class... Types>
    inline constexpr bool _Is_any_of_v = ::std::disjunction_v<::std::is_same<T, Types>...>;
}

#endif // _MSC_VER

/*-------------------------- Vector traits --------------------------*/

template <typename T>
struct _Is_2d_Vector
{
    static constexpr bool value = std::_Is_any_of_v< std::decay_t<T>, Vector<int32_t,2>, Vector<float_t,2>, Vector<uint32_t,2> >;
};

template<typename T>
inline constexpr bool is2dVector = _Is_2d_Vector<T>::value;

template <typename T>
struct _Is_3d_Vector
{
    static constexpr bool value = std::_Is_any_of_v< std::decay_t<T>, Vector<int32_t,3>, Vector<float_t,3>, Vector<uint32_t,3> >;
};

template <typename T>
inline constexpr bool is3dVector = _Is_3d_Vector<T>::value;

template <typename T>
struct _Is_4d_Vector
{
    static constexpr bool value = std::_Is_any_of_v< std::decay_t<T>, Vector<int32_t,4>, Vector<float_t,4>, Vector<uint32_t,4> >;
};

template <typename T>
inline constexpr bool is4dVector = _Is_4d_Vector<T>::value;

template <typename T>
struct _Is_Vector_Type
{
    static constexpr bool value = is2dVector<T> || is3dVector<T> || is4dVector<T> || std::is_same_v<T, ::DirectX::XMVECTOR>;
};

template <typename T>
inline constexpr bool isVectorType = _Is_Vector_Type<T>::value;

/*-------------------------------------------------------------------*/


/*-------------------------- Matrix traits --------------------------*/

template <typename T>
struct _Is_3x3_Matrix
{
    static constexpr bool value = std::_Is_any_of_v< std::decay_t<T>, Matrix<int32_t, 3, 3>, Matrix<float_t, 3, 3>, Matrix<uint32_t, 3, 3> >;
};

template <typename T>
inline constexpr bool is3x3Matrix = _Is_3x3_Matrix<T>::value;

template <typename T>
struct _Is_3x4_Matrix
{
    static constexpr bool value = std::_Is_any_of_v< std::decay_t<T>, Matrix<int32_t, 3, 4>, Matrix<float_t, 3, 4>, Matrix<uint32_t, 3, 4> >;
};

template <typename T>
inline constexpr bool is3x4Matrix = _Is_3x4_Matrix<T>::value;

template <typename T>
struct _Is_4x3_Matrix
{
    static constexpr bool value = std::_Is_any_of_v< std::decay_t<T>, Matrix<int32_t, 4, 3>, Matrix<float_t, 4, 3>, Matrix<uint32_t, 4, 3> >;
};

template <typename T>
inline constexpr bool is4x3Matrix = _Is_4x3_Matrix<T>::value;

template <typename T>
struct _Is_4x4_Matrix
{
    static constexpr bool value = std::_Is_any_of_v< std::decay_t<T>, Matrix<int32_t, 4, 4>, Matrix<float_t, 4, 4>, Matrix<uint32_t, 4, 4> >;
};

template <typename T>
inline constexpr bool is4x4Matrix = _Is_4x4_Matrix<T>::value;

template <typename T>
struct _Is_Matrix_Type
{
    static constexpr bool value = is3x3Matrix<T> || is3x4Matrix<T> || is4x3Matrix<T> || is4x4Matrix<T> || std::is_same_v<T, ::DirectX::XMMATRIX>;
};

template <typename T>
inline constexpr bool isMatrixType = _Is_Matrix_Type<T>::value;

/*-------------------------------------------------------------------*/
