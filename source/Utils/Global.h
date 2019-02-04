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
# define __FORCE_INLINE_EXP(...) __VA_ARGS__ __forceinline
#else
# define __FORCE_INLINE_EXP(...) [[gnu::always_inline]] __VA_ARGS__ inline
#endif

#define FORCE_INLINE __FORCE_INLINE_EXP()
#define FORCE_INLINE_STATIC __FORCE_INLINE_EXP(static)

#define __FORWARD_DECLARE_EXP(name, ...) __VA_ARGS__ name;

#define FORWARD_DECLARE_CLASS(name) __FORWARD_DECLARE_EXP(name, class)
#define FORWARD_DECLARE_STRUCT(name) __FORWARD_DECLARE_EXP(name, struct)

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
#  define __LINK_LIBRARY_EXP(...) __declspec(__VA_ARGS__)
#else
#  define __LINK_LIBRARY_EXP(...) __attribute__((visibility(#__VA_ARGS__)))
#endif

#ifdef _MSC_VER
#  define PYNG_LIBRARY_EXPORT __LINK_LIBRARY_EXP(dllexport)
#  define PYNG_LIBRARY_IMPORT __LINK_LIBRARY_EXP(dllimport)
#else
#  define PYNG_LIBRARY_EXPORT __LINK_LIBRARY_EXP(default)
#  define PYNG_LIBRARY_IMPORT __LINK_LIBRARY_EXP(default)
#endif

#define UNUSED(v) (void)v;
