#pragma once

#include <utility>

namespace Pyng
{
    enum Traverse { Vertical, Horizontal };
    
    template <class T, Traverse order>
    class matrix_iterator
    {
        typedef matrix_iterator<T, order> Type;

        matrix_iterator(T& data, int row, int column, bool reversed = false)
            : m_data(data), m_position(row, column), m_reversed(reversed)
        {  }
    
    public:
        typedef T DataType;
        // Iterator specific typedefs to be compliant with STL
        typedef typename T::value_type::iterator::pointer pointer;
        typedef typename T::value_type::iterator::reference reference;
        typedef typename T::value_type::iterator::value_type value_type;
        typedef typename T::value_type::iterator::difference_type difference_type;
        typedef typename T::value_type::iterator::iterator_category iterator_category;
    
        template <Traverse direction, class DataType>
        friend matrix_iterator<DataType, direction> begin(DataType&);
        template <Traverse direction, class DataType>
        friend matrix_iterator<DataType, direction> end(DataType&);
        template <Traverse direction, class DataType>
        friend matrix_iterator<DataType, direction> rbegin(DataType&);
        template <Traverse direction, class DataType>
        friend matrix_iterator<DataType, direction> rend(DataType&);

        static constexpr auto direction = order;

        matrix_iterator(Type&& other) = default;
        matrix_iterator(const Type &other) = default;

        Type& operator=(const Type &other)
        {
            m_data = other.m_data;
            m_reversed = other.m_reversed;
            m_position = other.m_position;
            return *this;
        }

        size_t row_size() const noexcept
        {
            if constexpr(order == Horizontal)
                return std::size(m_data.front());
            else if (order == Vertical)
                return std::size(m_data);
        }
    
        auto& operator*()
        {
            return m_data[m_position.first][m_position.second];
        }
        
        auto operator->()
        {
            return &this->operator*();
        }

        Type operator+(int value) const
        {
            return Type(*this) += value;
        }

        Type operator-(int value) const
        {
            return Type(*this) -= value;
        }

        Type& operator+=(int value)
        {
            for (int i = 0; i < value; ++i)
                operator++();

            return *this;
        }

        Type& operator-=(int value)
        {
            for (int i = 0; i < value; ++i)
                operator--();

            return *this;
        }
    
        int operator-(const Type& other) const
        {
            if (*this < other)
                return 0;
        
            Type iterator(*this);
        
            int acc = 0;
        
            for (;other != iterator; ++acc) {
                --iterator;
            }

            return acc;
        }

        Type& operator++()
        {
            return m_reversed ? decrement() : increment();
        }

        Type& operator--()
        {
            return m_reversed ? increment() : decrement();
        }

        Type& operator++(int)
        {
            Type temp(*this); ++(*this);
            return *this;
        }

        Type& operator--(int)
        {
            Type temp(*this); --(*this);
            return temp;
        }

        bool operator==(const Type& other) const
        {
            return m_position == other.m_position;
        }

        bool operator!=(const Type& other) const
        {
            return !this->operator==(other);
        }

        bool operator<(const Type& other) const
        {
            bool lessThan;
            
            if constexpr (order == Vertical) {
                lessThan = m_position.second != other.m_position.second ?
                    m_position.second < other.m_position.second :
                    m_position.first < other.m_position.first;
            } else if (order == Horizontal) {
                lessThan = m_position.first == other.m_position.first ?
                    m_position.second < other.m_position.second :
                    m_position.first < other.m_position.first;
            }

            return m_reversed ? !lessThan : lessThan;
        }

        bool operator<=(const Type& other) const
        {
            return (*this) < other || (*this) == other;
        }
    
    protected:
        Type& increment() {
            if constexpr(order == Horizontal) {
                if (m_position.second + 1 < std::size(m_data[0])) {
                    m_position.second++;
                } else {
                    m_position.first++;
                    m_position.second = 0;
                }
            } else if (order == Vertical) {
                if (m_position.first + 1 < std::size(m_data)) {
                    m_position.first++;
                } else {
                    m_position.second++;
                    m_position.first = 0;
                }
            }

            return *this;
        }

        Type& decrement() {
            if constexpr(order == Horizontal) {
                if (m_position.second > 0) {
                    m_position.second--;
                } else {
                    m_position.first--;
                    m_position.second = std::size(m_data[0]) - 1;
                }
            } else if (order == Vertical) {
                if (m_position.first > 0) {
                    m_position.first--;
                } else {
                    m_position.second--;
                    m_position.first = std::size(m_data) - 1;
                }
            }

            return *this;
        }

    private:
        T& m_data;
        bool m_reversed;
        std::pair<int, int> m_position;
    };

    template <Traverse order, class DataType>
    matrix_iterator<DataType, order> begin(DataType& matrix)
    {
        return matrix_iterator<DataType,order>(matrix, 0, 0, false);
    }

    template <Traverse order, class DataType>
    matrix_iterator<DataType, order> end(DataType& matrix)
    {
        if constexpr (order == Vertical) {
            return matrix_iterator<DataType,order>(matrix, 0, std::size(matrix[0]), false);
        } else if (order == Horizontal) {
            return matrix_iterator<DataType,order>(matrix, std::size(matrix), 0, false);
        }
    }

    template <Traverse order, class DataType>
    matrix_iterator<DataType, order> rbegin(DataType& matrix)
    {
        return matrix_iterator<DataType,order>(matrix, std::size(matrix) - 1, std::size(matrix[0]) - 1, true);
    }

    template <Traverse order, class DataType>
    matrix_iterator<DataType, order> rend(DataType& matrix)
    {
        if constexpr (order == Horizontal) {
            return matrix_iterator<DataType,order>(matrix, -1, std::size(matrix[0]) - 1, true);
        } else if (order == Vertical) {
            return matrix_iterator<DataType,order>(matrix, std::size(matrix) - 1, -1, true);
        }
    }
}
