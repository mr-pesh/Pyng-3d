#pragma once

#include <array>

#if defined(__CPP_AMP_ACCELERATION)
# include <amp.h>
#elif defined(__cpp_lib_execution)
# include <execution>
#endif

template <typename T, int_fast16_t rows_V, int_fast16_t columns_V>
class Matrix : public std::array <T, rows_V * columns_V>
{
    static_assert(rows_V > 0 && columns_V > 0, "Matrix can't be of zero or negative size");
    
    typedef array<T, rows_V * columns_V> Base;
    typedef Matrix<T, rows_V, columns_V> Type;
    typedef Matrix<T, columns_V, rows_V> Transposed;

public:

    static constexpr auto rows = rows_V;
    static constexpr auto columns = columns_V;

    size_t size() { return Base::size(); }

    Type operator*(const T scalar) const
    {
        return Type(*this) *= scalar;
    }

    Type& operator+(const Type &other) const
    {
        return Type(*this) += other;
    }

    T operator()(int_fast16_t row, int_fast16_t column) const
    {
        return (*this)[row * columns + column];
    }

    T& operator()(int_fast16_t row, int_fast16_t column)
    {
        return (*this)[row * columns + column];
    }

    Transposed transpose() const
    {
        Transposed result;

    #ifdef __CPP_AMP_ACCELERATION
        concurrency::array_view<Type::value_type, 1> source_v(
            Base::size(), const_cast<Type::pointer>(Base::data()));
        concurrency::array_view<Transposed::value_type> result_v(result);

        concurrency::parallel_for_each(result_v.extent, [=](concurrency::index<1> index) restrict(amp) {
            const auto inner = index[0];
            const auto i = inner / rows;
            const auto j = inner % rows;
            result_v[index] = source_v(columns * j + i);
        });

        result_v.synchronize();
    #else
        #pragma omp parallel for
        for (int_fast16_t n = 0; n < rows * columns; ++n) {
            const auto i = n / rows;
            const auto j = n % rows;
            result[n] = (*this)[columns * j + i];
        }
    #endif
        return result;
    }

    template <typename Number, typename = typename std::enable_if_t< std::is_arithmetic_v<Number> >>
    auto operator*(const Number scalar) const
    {
        using ResultType = Matrix<decltype(Base::front() * scalar), rows, columns>;

        ResultType result;

    #ifdef __CPP_AMP_ACCELERATION
        concurrency::array_view<Type::value_type, 1> source_v(
            Base::size(), const_cast<Type::pointer>(Base::data()));
        concurrency::array_view<ResultType::value_type, 1> result_v(result);

        concurrency::parallel_for_each(
            result_v.extent, [=](concurrency::index<1> index) restrict(amp) {
            result_v[index] = source_v[index] * scalar;
        });
        result_v.synchronize();

    #elif defined(__cpp_lib_execution)
        std::transform(
            std::execution::par_unseq,
            this->cbegin(), this->cend(), result.begin(),
            [=](const ResultType::value_type value) { return value * scalar; }
        );
    #else
        #pragma omp parallel for
        for (int_fast16_t i = 0; i < static_cast<int_fast16_t>(result.size()); ++i) {
            result[i] = (*this)[i] * scalar;
        }
#endif
        return result;
    }

    template <class Multiplier, class = typename std::enable_if_t< std::is_class_v<Multiplier> >>
    auto operator*(const Multiplier &other)
    {
        static_assert(Type::columns == Multiplier::rows, "Two matrices are not consistant for multiplying");
        
        using ResultType = Matrix<decltype(Base::front() * other.front()), Type::rows, Multiplier::columns>;

        ResultType result = { 0 };

    #ifdef __CPP_AMP_ACCELERATION
        concurrency::array_view<Type::value_type, 2> source_v(
            Type::rows, Type::columns, const_cast<Type::pointer>(Base::data()));
        concurrency::array_view<Multiplier::value_type, 2> multiplier_v(
            Multiplier::rows, Multiplier::columns, const_cast<Multiplier::pointer>(other.data()));
        concurrency::array_view<ResultType::value_type, 2> result_v(
            ResultType::rows, ResultType::columns, result);

        concurrency::parallel_for_each(
            result_v.extent, [=](concurrency::index<2> index) restrict(amp) {
                const auto row = index[0];
                const auto column = index[1];
                for (int_fast16_t inner = 0; inner < Type::columns; ++inner) {
                    result_v[index] += source_v(row, inner) * multiplier_v(inner, column);
                }
            }
        );

        result_v.synchronize();
    #else
        #pragma omp parallel for
        for (int_fast16_t i = 0; i < Type::rows; i++) {
            #pragma omp parallel for
            for (int_fast16_t j = 0; j < Multiplier::columns; ++j) {
                for (int_fast16_t inner = 0; inner < Type::columns; ++inner) {
                    result(i, j) += (*this)(i, inner) * other(inner, j);
                }
            }
        }
    #endif
        return result;
    }

    template <typename Number, typename = typename std::enable_if_t< std::is_arithmetic_v<Number> >>
    Type& operator*=(const Number scalar)
    {
    #ifdef __CPP_AMP_ACCELERATION
        concurrency::array_view<Type::value_type, 1> source_v(*this);
        concurrency::parallel_for_each(
            source_v.extent,[=] (concurrency::index<1> index) restrict(amp) {
                source_v[index] *= scalar;
        });
        source_v.synchronize();
    #elif defined(__cpp_lib_execution)
        std::for_each(
            std::execution::par_unseq,
            this->begin(), this->end(), [=] (T &value) { return value *= scalar; }
        );
    #else
        #pragma omp parallel for
        for (int_fast16_t i = 0; i < static_cast<int_fast16_t>(Base::size()); ++i) {
            (*this)[i] *= scalar;
        }
    #endif
        return *this;
    }

    Type& operator+=(const Type &other)
    {
    #ifdef __CPP_AMP_ACCELERATION
        concurrency::array_view<Type::value_type, 1> add_v(
            other.size(), const_cast<Type::pointer>(other.data()));
        concurrency::array_view<Type::value_type, 1> source_v(*this);

        concurrency::parallel_for_each(
            source_v.extent, [=](concurrency::index<1> index) restrict(amp) {
            source_v[index] += add_v[index];
        });
        source_v.synchronize();
    #elif defined(__cpp_lib_execution)
        std::transform(
            std::execution::par_unseq,
            this->cbegin(), this->cend(), other.cbegin(), this->begin(), std::plus<T>()
        );
    #else
        #pragma omp parallel for
        for (int_fast16_t i = 0; i < static_cast<int_fast16_t>(Base::size()); ++i) {
            (*this)[i] += other[i];
        }
    #endif
        return *this;
    }
};
