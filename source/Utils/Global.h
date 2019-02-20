#pragma once

#include <memory>

#define PYNG_DISABLE_COPY(Class)           \
    Class (const Class&) = delete;         \
    Class &operator=(const Class&) = delete;

#define DECLARE_PYNG_SINGLETON(Type)       \
    PYNG_DISABLE_COPY(Type)                \
public:                                    \
    Type();                                \
    static Type *instance();               \

#define DEFINE_PYNG_SINGLETON(Type)                  \
    Type::Type()                                     \
    {  }                                             \
    static Type *Type::instance()                    \
    {                                                \
        static auto ptr = std::make_unique<Type>();  \
        return ptr.get();                            \
    }

#ifdef _MSC_VER
# define FORCE_INLINE __forceinline
#else
# ifndef __always_inline
# define __always_inline inline __attribute__ ((__always_inline__))
# endif
# define FORCE_INLINE __always_inline
#endif

#define FORWARD_DECLARE_CLASS(name) class name;
#define FORWARD_DECLARE_STRUCT(name) struct name;

#ifdef __GNUC__
#  define UNUSED [[gnu::unused]]
#  define NODISCARD [[gnu::warn_unused_result]]
#  define DEPRECATED [[gnu::deprecated]]
#else
#  define UNUSED [[maybe_unused]]
#  define NODISCARD [[nodiscard]]
#  define DEPRECATED [[deprecated]]
#endif

#ifdef _MSC_VER
#  define EXPECTED(expr) (expr)
#  define UNLIKELY(expr) (expr)
#elif defined (__GNUC__)
#  define EXPECTED(expr) __builtin_expect(!!(expr), true)
#  define UNLIKELY(expr) __builtin_expect(!!(expr), false)
#endif

#ifdef _MSC_VER
#  define PYNG_LIBRARY_EXPORT __declspec(dllexport)
#  define PYNG_LIBRARY_IMPORT __declspec(dllimport)
#else
#  define PYNG_LIBRARY_EXPORT __attribute__((visibility("default")))
#  define PYNG_LIBRARY_IMPORT __attribute__((visibility("default")))
#endif

#define UNUSED(v) (void)v;
