#pragma once

#include <Utils/Global.h>

#ifdef _MSC_VER
# pragma warning(suppress: 4005)
# define alloca(size)  _malloca(size)
#elif defined (__GNUC__)
# ifndef alloca
# define alloca(size) __builtin_alloca(size)
# endif
#endif

template <class T>
struct HeapAllocationPolicy
{
    template <class ...Args>
    FORCE_INLINE_STATIC T *Create(Args ...args) noexcept (std::is_nothrow_constructible<T>::value)
    {
        return new T(args...);
    }
    FORCE_INLINE_STATIC void Destroy(T *ptr) noexcept (std::is_nothrow_destructible<T>::value)
    {
        delete ptr;
    }
};

template <class T>
struct StackAllocationPolicy
{
    template <class ...Args>
    FORCE_INLINE_STATIC T *Create(Args ...args) noexcept (std::is_nothrow_constructible<T>::value)
    {
        return new (alloca(sizeof(T))) T(args...);
    }

    FORCE_INLINE_STATIC void Destroy(UNUSED T *ptr) noexcept
    {
    #ifdef _MSC_VER
        _freea((void*)ptr);
    #endif
    }
};


template <template <class> class AllocationPolicy, class T>
class UniquePointer
{
    PYNG_DISABLE_COPY(UniquePointer)

public:
    FORCE_INLINE UniquePointer(T *ptr) noexcept (std::is_nothrow_constructible<T>::value)
        : data(ptr)
    {  }
    FORCE_INLINE ~UniquePointer() noexcept (std::is_nothrow_destructible<T>::value)
    {
        AllocationPolicy<T>::Destroy(data);
    }
    FORCE_INLINE UniquePointer(UniquePointer&&) noexcept = default;

    T *get() const noexcept { return data; }

    T *operator->() const noexcept { return get(); }

    std::add_lvalue_reference_t<T> operator*() const noexcept
    {
        return *get();
    }

    explicit operator bool() const noexcept { return data; }

private:
    T *data;
};


template <template <class>
          class AllocationPolicy, class Type, class ...Args>
FORCE_INLINE UniquePointer<AllocationPolicy, Type> AllocateUnique(Args ...args) noexcept (std::is_nothrow_constructible<Type>::value)
{
    return UniquePointer<AllocationPolicy, Type>(AllocationPolicy<Type>::Create(args...));
}
