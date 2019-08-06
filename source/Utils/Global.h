#pragma once

#ifdef _MSC_VER
# define FORCE_INLINE __forceinline
#else
# include <sys/cdefs.h>
# ifndef __always_inline
# if defined(__GNUC__) && (defined(__APPLE__) || defined(__DARWIN_X11__) || defined(__MACOSX__) || defined(__xlC__) || defined(__xlc__))
# define __always_inline __header_always_inline
# else
# define __always_inline inline __attribute__ ((__always_inline__))
# endif
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
