#pragma once

#include <type_traits>
#include "private/ArrayView_base.h"

template <typename T>
class ArrayView : public ArrayView_Base
{
public:
    template <class = std::enable_if_t< std::is_array_v < T > >>
    explicit ArrayView(T &array)
        : ArrayView_Base(std::size(array)), data(array)
    { }

    template <bool = std::is_class_v< T::iterator >>
    explicit ArrayView(T &container)
        : ArrayView_Base(container.size()), data(container)
    { }

private:
    T &data;
};