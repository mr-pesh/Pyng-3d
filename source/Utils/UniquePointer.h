#pragma once

#include <Utils/Global.h>
#include <Utils/Memory.h>

template <class T>
struct HeapAllocationPolicy
{
    template <class Type = T, class ...Args,
        std::enable_if_t<!std::is_array_v<T>, int> = 0>
    FORCE_INLINE_STATIC Type *Create(Args&& ...args) noexcept (std::is_nothrow_constructible_v<Type>)
    {
        return new (std::nothrow) Type(std::forward<Args>(args)...);
    }

    template <class Type = std::remove_extent_t<T>>
    FORCE_INLINE_STATIC Type *Create(size_t size) noexcept (std::is_nothrow_constructible_v<Type>)
    {
        return new (std::nothrow) Type[size];
    }

    template <class Type = std::remove_extent_t<T>>
    FORCE_INLINE_STATIC void Destroy(Type *ptr) noexcept (std::is_nothrow_destructible_v<Type>)
    {
        if constexpr (std::is_array_v<T>) {
            delete [] ptr;
        } else {
            delete ptr;
        }
    }
};

template <class T>
struct StackAllocationPolicy
{
    template <class Type = T, class ...Args,
        std::enable_if_t<std::is_trivially_destructible_v<Type> && !std::is_array_v<T>, int> = 0>
    FORCE_INLINE_STATIC Type *Create(Args&& ...args) noexcept (std::is_nothrow_constructible_v<T>)
    {
        return new (_malloca(sizeof(Type))) Type(args...);
    }

    template <class Type = std::remove_extent_t<T>,
        std::enable_if_t<std::is_trivially_destructible_v<Type> && std::is_array_v<T>, int> = 0>
    FORCE_INLINE_STATIC Type *Create(size_t size) noexcept (std::is_nothrow_constructible_v<T>)
    {
        return new (_malloca(sizeof(Type) * size)) Type[size];
    }

    template <class Type = std::remove_extent_t<T>>
    FORCE_INLINE_STATIC void Destroy(Type *ptr) noexcept
    {
        _freea((void*)ptr);
    }
};

template <class T, template <class> class AllocationPolicy = HeapAllocationPolicy>
class UniquePointer
{
    PYNG_DISABLE_COPY(UniquePointer)

public:
    typedef std::remove_extent_t<T> element_type;
    typedef std::add_pointer_t<element_type> pointer;
    typedef std::add_lvalue_reference_t<element_type> reference;

    constexpr UniquePointer() noexcept
        : data_() { }

    constexpr UniquePointer(std::nullptr_t) noexcept
        : data_() { }

    FORCE_INLINE UniquePointer(UniquePointer&&) noexcept = default;

    FORCE_INLINE explicit UniquePointer(pointer p) noexcept (std::is_nothrow_constructible_v<element_type>)
        : data_(p) { }

    ~UniquePointer() noexcept (std::is_nothrow_destructible_v<element_type>)
    {
        AllocationPolicy<T>::Destroy(data_);
    }

    UniquePointer& operator=(UniquePointer&& other) noexcept = default;

    UniquePointer& operator=(pointer p) noexcept
    {
        reset(p);
        return *this;
    }

    UniquePointer& operator=(std::nullptr_t) noexcept
    {
        reset();
        return *this;
    }

    explicit operator bool() const noexcept
    {
        return data_;
    }

    NODISCARD pointer get() const noexcept
    {
        return data_;
    }

    NODISCARD const pointer *operator&() const noexcept
    {
        return std::addressof(data_);
    }

    NODISCARD auto operator&() noexcept
    {
        reset();
        return std::addressof(data_);
    }

    NODISCARD pointer operator->() const noexcept
    {
        return get();
    }

    NODISCARD reference operator*() const noexcept
    {
        return *get();
    }

    template <class Type = T, std::enable_if_t<std::is_array_v<Type>, int> = 0>
    NODISCARD reference operator[](std::ptrdiff_t index) const noexcept
    {
        return get()[index];
    }

    pointer release() noexcept
    {
        pointer temp = get();
        data_ = pointer();
        return temp;
    }

    void reset(pointer ptr = pointer()) noexcept
    {
        pointer old = get(); data_ = ptr;

        if (old != pointer())
        {
            AllocationPolicy<T>::Destroy(old);
        }
    }

    void swap(UniquePointer& other) noexcept
    {
        std::swap(data_, other.data_);
    }

private:
    pointer data_;
};


template <class T1, template <class> class P1, class T2, template <class> class P2>
inline bool operator==(const UniquePointer<T1,P1> &x, const UniquePointer<T2,P2> &y) noexcept
{
    return x.get() == y.get();
}

template <class T1, template <class> class P1, class T2, template <class> class P2>
inline bool operator!=(const UniquePointer<T1, P1> &x, const UniquePointer<T2, P2> &y) noexcept
{
    return x.get() != y.get();
}

template <class T1, template <class> class P1, class T2, template <class> class P2,
          class pointer = std::common_type_t<typename UniquePointer<T1,P1>::pointer, typename UniquePointer<T2,P2>::pointer>
          >
inline bool operator<(const UniquePointer<T1, P1> &x, const UniquePointer<T2, P2> &y) noexcept
{
    return std::less<pointer>()(x.get(), y.get());
}

template <class T1, template <class> class P1, class T2, template <class> class P2>
inline bool operator<=(const UniquePointer<T1, P1> &x, const UniquePointer<T2, P2> &y) noexcept
{
    return !(x < y);
}

template <class T1, template <class> class P1, class T2, template <class> class P2>
inline bool operator>(const UniquePointer<T1, P1> &x, const UniquePointer<T2, P2> &y) noexcept
{
    return y < x;
}

template <class T1, template <class> class P1, class T2, template <class> class P2>
inline bool operator>=(const UniquePointer<T1, P1> &x, const UniquePointer<T2, P2> &y) noexcept
{
    return !(y < x);
}

template <class T, template <class> class P>
inline bool operator==(const UniquePointer<T,P> &x, std::nullptr_t) noexcept
{
    return !x;
}

template <class T, template <class> class P>
inline bool operator==(std::nullptr_t, const UniquePointer<T,P> &x) noexcept
{
    return !x;
}

template <class T, template <class> class P>
inline bool operator!=(const UniquePointer<T,P> &x, std::nullptr_t) noexcept
{
    return (bool)x;
}

template <class T, template <class> class P>
inline bool operator!=(std::nullptr_t, const UniquePointer<T,P> &x) noexcept
{
    return (bool)x;
}

template <class T, template <class> class P,
          class pointer = typename UniquePointer<T, P>::pointer
          >
inline bool operator<(const UniquePointer<T,P> &x, std::nullptr_t) noexcept
{
    return std::less<pointer>()(x.get(), nullptr);
}

template <class T, template <class> class P,
          class pointer = typename UniquePointer<T,P>::pointer
          >
inline bool operator<(std::nullptr_t, const UniquePointer<T,P> &y) noexcept
{
    return std::less<pointer>()(nullptr, y.get());
}

template <class T, template <class> class P>
inline bool operator<=(const UniquePointer<T,P> &x, std::nullptr_t) noexcept
{
    return !(nullptr < x);
}

template <class T, template <class> class P>
inline bool operator<=(std::nullptr_t, const UniquePointer<T,P> &y) noexcept
{
    return !(y < nullptr);
}

template <class T, template <class> class P>
inline bool operator>(const UniquePointer<T,P> &x, std::nullptr_t) noexcept
{
    return (nullptr < x);
}

template <class T, template <class> class P>
inline bool operator>(std::nullptr_t, const UniquePointer<T,P> &y) noexcept
{
    return (y < nullptr);
}

template <class T, template <class> class P>
inline bool operator>=(const UniquePointer<T,P> &x, std::nullptr_t) noexcept
{
    return !(x < nullptr);
}

template <class T, template <class> class P>
inline bool operator>=(std::nullptr_t, const UniquePointer<T,P> &y) noexcept
{
    return !(nullptr < y);
}

template <class Char, class Traits,
          class PointerType, template <class> class AllocationPolicy,
          class Stream = std::basic_ostream<Char, Traits>
          >
inline Stream &operator<<(Stream &ostream, const UniquePointer<PointerType, AllocationPolicy> &ptr)
{
    return ostream << ptr.get();
}

template <class Type,
          template <class> class AllocationPolicy = HeapAllocationPolicy,
          class ...Args, std::enable_if_t<!std::is_array_v<Type>, int> = 0
          >
NODISCARD FORCE_INLINE UniquePointer<Type, AllocationPolicy> AllocateUnique(Args&& ...args) noexcept (std::is_nothrow_constructible_v<Type>)
{
    return UniquePointer<Type, AllocationPolicy>(AllocationPolicy<Type>::Create(std::forward<Args>(args)...));
}

template <class Type,
          template <class> class AllocationPolicy = HeapAllocationPolicy,
          std::enable_if_t<std::is_array_v<Type> && std::extent_v<Type> == 0, int> = 0,
          typename _Ty = std::remove_extent_t<Type>
          >
NODISCARD FORCE_INLINE UniquePointer<Type, AllocationPolicy> AllocateUnique(size_t size) noexcept (std::is_nothrow_constructible_v<_Ty>)
{
    return UniquePointer<Type, AllocationPolicy>(AllocationPolicy<Type>::Create(size));
}

template<class Type,
         template <class> class AllocationPolicy = HeapAllocationPolicy,
         class... Args, std::enable_if_t<std::extent_v<Type> != 0, int> = 0
         >
UniquePointer<Type, AllocationPolicy> AllocateUnique(Args&&...) = delete;

namespace std
{
    template <class Type, template <class> class AllocationPolicy>
    void swap(UniquePointer<Type, AllocationPolicy> &lhs, UniquePointer<Type, AllocationPolicy> &rhs) noexcept
    {
        lhs.swap(rhs);
    }

    template <class Type, template <class> class AllocationPolicy>
    struct hash<UniquePointer<Type, AllocationPolicy>>
    {
        NODISCARD size_t operator()(const UniquePointer<Type, AllocationPolicy> &ptr) const noexcept
        {
            return hash<typename UniquePointer<Type, AllocationPolicy>::pointer>()(ptr.get());
        }
    };
}
