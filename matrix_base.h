#pragma once

#include <array>

template <typename T, size_t rows, size_t columns>
struct Matrix :
    std::array <T, rows * columns>
{
    typedef Matrix<T, rows, columns> Type;

    Type transpose()
    {
        Type result;
        #pragma omp parallel for
        for (int n = 0; n < rows * columns; ++n) {
            const auto i = n / rows;
            const auto j = n % rows;
            result[n] = *this[columns * j + i];
        }

        return result;
    }
};
