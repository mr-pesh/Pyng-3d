#pragma once

#include "private/ArrayView_base.h"

template <typename T>
class ArrayView : public ArrayView_Base
{
public:
    template <class = std::enable_if_t< std::is_array<T>::value >>
    explicit ArrayView(T &array)
        : ArrayView_Base(std::size(array)), data(array)
    { }

    template <bool = std::is_class<T::iterator>::value>
    explicit ArrayView(T &container)
        : ArrayView_Base(container.size()), data(container)
    { }

private:
    T &data;
};
