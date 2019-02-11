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
    template <class Type = T, class ...Args>
    FORCE_INLINE_STATIC Type *Create(Args&& ...args) noexcept (std::is_nothrow_constructible_v<Type>)
    {
        return new Type(std::forward<Args>(args)...);
    }

    template <class Type = std::remove_extent_t<T>>
    FORCE_INLINE_STATIC Type *Create(size_t size) noexcept (std::is_nothrow_constructible_v<Type>)
    {
        return new Type[size];
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
    template <class Type = T, class ...Args>
    FORCE_INLINE_STATIC T *Create(Args&& ...args) noexcept (std::is_nothrow_constructible_v<T>)
    {
        return new (alloca(sizeof(Type))) Type(args...);
    }

    template <class Type = std::remove_extent_t<T>>
    FORCE_INLINE_STATIC Type *Create(size_t size) noexcept (std::is_nothrow_constructible_v<T>)
    {
        return new (alloca(sizeof(Type) * size)) Type[size];
    }

    FORCE_INLINE_STATIC void Destroy(UNUSED T *ptr) noexcept
    {
    #ifdef _MSC_VER
        _freea((void*)ptr);
    #endif
    }
};


template <class T, template <class> class AllocationPolicy = HeapAllocationPolicy>
class UniquePointer
{
    PYNG_DISABLE_COPY(UniquePointer)

public:
    using Type = std::remove_extent_t<T>;

    FORCE_INLINE UniquePointer(Type *ptr) noexcept (std::is_nothrow_constructible_v<Type>)
        : data(ptr)
    {  }

    FORCE_INLINE ~UniquePointer() noexcept (std::is_nothrow_destructible_v<Type>)
    {
        AllocationPolicy<T>::Destroy(data);
    }

    FORCE_INLINE UniquePointer(UniquePointer&&) noexcept = default;

    Type *get() const noexcept { return data; }
    Type &operator*() const noexcept { return *get(); }
    Type *operator->() const noexcept { return get(); }
    explicit operator bool() const noexcept { return data; }

    template <class _Ty = T, std::enable_if_t<std::is_array_v<_Ty>, int> = 0>
    NODISCARD Type& operator[](std::ptrdiff_t index) const noexcept
    {
        return get()[index];
    }

private:
    Type *data;
};


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
          typename _Ty = std::remove_extent_t<Type>>
NODISCARD FORCE_INLINE UniquePointer<Type, AllocationPolicy> AllocateUnique(size_t size) noexcept (std::is_nothrow_constructible_v<_Ty>)
{
    return UniquePointer<Type, AllocationPolicy>(AllocationPolicy<Type>::Create(size));
}

template<class Type,
         template <class> class AllocationPolicy = HeapAllocationPolicy,
         class... Args, std::enable_if_t<std::extent_v<Type> != 0, int> = 0
         >
UniquePointer<Type, AllocationPolicy> AllocateUnique(Args&&...) = delete;
