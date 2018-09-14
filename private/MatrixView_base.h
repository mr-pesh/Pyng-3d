#pragma once

#include "ArrayView_base.h"

class MatrixView_Base : public ArrayView_Base
{
protected:
    MatrixView_Base(int_fast16_t rows, int_fast16_t columns, size_t size)
        : ArrayView_Base(size), m_rows(rows), m_columns(columns)
    { }

public:
    int_fast16_t &rows() { return m_rows; }
    int_fast16_t &columns() { return m_columns; }

    int_fast16_t rows() const  { return m_rows; }
    int_fast16_t columns() const { return m_columns; }

    void transpose()
    {
        std::swap(m_rows, m_columns);
    }

private:
    int_fast16_t m_rows;
    int_fast16_t m_columns;
};