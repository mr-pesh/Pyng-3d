#pragma once

#include "private/MatrixView_base.h"

template <typename T>
class MatrixView : public MatrixView_Base
{
    using Base = MatrixView_Base;
    using Type = MatrixView< T >;

public:
    template <class = std::enable_if_t< std::is_same< decltype(T::columns), decltype(T::rows) >::value >>
    explicit MatrixView(T &matrix)
        : MatrixView_Base(T::rows, T::columns, matrix.size()), data(matrix)
    { }

    template <class = std::enable_if_t< std::is_array<T>::value >>
    explicit MatrixView(T &array, int_fast16_t rows, int_fast16_t columns)
        : MatrixView_Base(rows, columns, std::size(array)), data(array)
    { }

    template <bool = std::is_class<T::iterator>::value>
    explicit MatrixView(T &container, int_fast16_t rows, int_fast16_t columns)
        : MatrixView_Base(rows, columns, container.size()), data(container)
    { }

    Type &transpose()
    {
        Base::transpose();
        return *this;
    }

    auto& operator()(int_fast16_t row, int_fast16_t column)
    {
        return data[row * columns() + column];
    }

    auto operator()(int_fast16_t row, int_fast16_t column) const
    {
        return data[row * columns() + column];
    }

private:
    T &data;
};
