#pragma once

#include <iterator>

template <class V>
class XMVectorIterator
{
    constexpr static int32_t vectorLength = sizeof(V) / sizeof(float);

    XMVectorIterator(const V &vec, int32_t position = 0)
        : data_(vec), index_(std::clamp(position, 0, vectorLength))
    {  }

public:
    typedef std::random_access_iterator_tag  iterator_category;
    typedef decltype(std::declval<V>().x)    value_type;
    typedef std::ptrdiff_t                   difference_type;
    typedef const value_type *               pointer;
    typedef const value_type &               reference;

    XMVectorIterator& operator++() noexcept { index_++; return *this; }
    XMVectorIterator& operator--() noexcept { index_--; return *this; }

    XMVectorIterator operator+(const int value) const { return XMVectorIterator(data_, index_ + value); }
    XMVectorIterator operator-(const int value) const { return XMVectorIterator(data_, index_ - value); }

    XMVectorIterator operator+(const XMVectorIterator &other) const { return XMVectorIterator(data_, this->index_ + other.index_); }
    XMVectorIterator operator-(const XMVectorIterator &other) const { return XMVectorIterator(data_, this->index_ - other.index_); }

    bool operator==(const XMVectorIterator &other) const noexcept { return this->data_ == other.data_ && this->index_ == other.index_; }
    bool operator!=(const XMVectorIterator &other) const noexcept { return this->data_ != other.data_ || this->index_ != other.index_; }

    pointer get(int32_t index) const noexcept { return reinterpret_cast<pointer>(&data_) + index; }

    pointer operator->() const noexcept { return get(index_); }
    reference operator*() const noexcept { return *get(index_); }

    friend constexpr XMVectorIterator std::begin(const V &vector) noexcept;
    friend constexpr XMVectorIterator std::end(const V &vector) noexcept;

private:
    const V &data_;
    int32_t index_;
};

namespace std
{
    template <class V>
    constexpr XMVectorIterator<V> begin(const V &vector) noexcept
    {
        return XMVectorIterator(vector, 0);
    }

    template <class V>
    constexpr XMVectorIterator<V> end(const V &vector) noexcept
    {
        return XMVectorIterator(vector, XMVectorIterator<V>::vectorLength);
    }
}