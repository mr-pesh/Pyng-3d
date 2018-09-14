#pragma once

#include <cstdint>

class ArrayView_Base
{
protected:
    ArrayView_Base(size_t size) : m_size(size)
    { }

    size_t size() const { return m_size; }

private:
    size_t m_size;
};