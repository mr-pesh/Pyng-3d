#pragma once

#include <array>

template <typename T, uint_fast16_t rows, uint_fast16_t columns>
struct Matrix :
    std::array <T, rows * columns>
{
    using Type = Matrix<T, rows, columns>;

    template <typename ResultType = Matrix<T, columns, rows> >
    ResultType transpose()
    {
        ResultType result;
        #pragma omp parallel for
        for (uint_fast16_t n = 0; n < rows * columns; ++n) {
            const auto i = n / rows;
            const auto j = n % rows;
            result[n] = (*this)[columns * j + i];
        }

        return result;
    }
};
