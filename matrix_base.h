#pragma once

#include <array>

template <typename T, uint_fast16_t rows, uint_fast16_t columns>
struct Matrix :
    std::array <T, rows * columns>
{
    static_assert(rows > 0 && columns > 0, "Matrix can't be of zero or negative size");
    
    typedef Matrix<T, rows, columns> Type;
    typedef Matrix<T, columns, rows> Transposed;

    Transposed transpose()
    {
        Transposed result;
        #pragma omp parallel for
        for (uint_fast16_t n = 0; n < rows * columns; ++n) {
            const auto i = n / rows;
            const auto j = n % rows;
            result[n] = (*this)[columns * j + i];
        }

        return result;
    }

    template <typename Number>
    Type& operator*=(const Number scalar) {
        static_assert(std::is_arithmetic<Number>::value);
        #pragma omp parallel for
        for (uint_fast16_t i = 0; i < size(); ++i) {
            (*this)[i] *= scalar;
        }
        return *this;
    }

    template <typename Number>
    inline Type operator*(const Number scalar) {
        return Type(*this) *= scalar;
    }

    Type& operator+=(const Type &other) {
        #pragma omp parallel for
        for (uint_fast16_t i = 0; i < size(); ++i) {
            (*this)[i] += other[i];
        }
        return *this;
    }

    inline Type& operator+(const Type &other) {
        return Type(*this) += other;
    }
};
