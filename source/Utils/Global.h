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
# define FORCE_INLINE_EXP(...) __VA_ARGS__ __forceinline
#else
# define FORCE_INLINE_EXP(...) [[gnu::always_inline]] __VA_ARGS__ inline
#endif

#define FORCE_INLINE   FORCE_INLINE_EXP()
#define FORCE_INLINE_S FORCE_INLINE_EXP(static)


#define FORWARD_DECLARE_EXP(name, ...) __VA_ARGS__ name;

#define FORWARD_DECLARE_CLASS (name) FORWARD_DECLARE_EXP(name, class)
#define FORWARD_DECLARE_STRUCT(name) FORWARD_DECLARE_EXP(name, struct)


#ifdef __GNUC__
#  define UNUSED      [[gnu::unused]]
#  define NODISCARD   [[gnu::warn_unused_result]]
#  define DEPRECATED  [[gnu::deprecated]]
#else
#  define UNUSED [[maybe_unused]]
#  define NODISCARD [[nodiscard]]
#  define DEPRECATED [[deprecated]]
#endif

#ifdef _MSC_VER
#  define LIKELY(expr)
#  define UNLIKELY(expr)
#elif defined (__GNUC__)
#  define LIKELY(expr)    __builtin_expect(!!(expr), true)
#  define UNLIKELY(expr)  __builtin_expect(!!(expr), false)
#endif

#ifdef _MSC_VER
#  define LINK_LIBRARY_EXP(...) __declspec(__VA_ARGS__)
#else
#  define LINK_LIBRARY_EXP(...) __attribute__((visibility(#__VA_ARGS__)))
#endif

#ifdef _WIN32
#    define LIBRARY_EXPORT LINK_LIBRARY_EXP(dllexport)
#    define LIBRARY_IMPORT LINK_LIBRARY_EXP(dllimport)
#else
#    define LIBRARY_EXPORT LINK_LIBRARY_EXP(default)
#    define LIBRARY_IMPORT LINK_LIBRARY_EXP(default)
#endif

#define UNUSED(v) (void)v;