#pragma once

#ifdef _MSC_VER
# include <malloc.h>
#else

#include <cassert>
#include <cstdlib>

#if defined (__GNUC__)
# ifndef alloca
# define alloca(size) __builtin_alloca(size)
# endif
#endif

#if defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__) || defined(__ia64__) || defined(__powerpc64__)
# define __ALLOCA_MARKER_SIZE 16
#else
# define __ALLOCA_MARKER_SIZE 8
#endif

#define __ALLOCA_THRESHOLD 1024

static constexpr unsigned int __ALLOCA_HEAP_MARKER  = 0xDDDD;
static constexpr unsigned int __ALLOCA_STACK_MARKER = 0xCCCC;

inline void* __markAlloca(void *ptr, unsigned int allocaMarker)
{
    if (ptr)
    {
        *reinterpret_cast<unsigned int*>(ptr) = allocaMarker;
        ptr = reinterpret_cast<char*>(ptr) + __ALLOCA_MARKER_SIZE;
    }
    return ptr;
}

inline size_t __allocaComputeSize(size_t size)
{
    size_t markedSize = size + __ALLOCA_MARKER_SIZE;
    return markedSize > size ? markedSize : 0;
}


#ifndef NDEBUG

#define _malloca(size)                                                           \
    (__allocaComputeSize(size) != 0                                              \
        ? __markAlloca(malloc(__allocaComputeSize(size)), __ALLOCA_HEAP_MARKER)  \
        : reinterpret_cast<void*>(NULL))

#else

#define _malloca(size)                                                                   \
    (__allocaComputeSize(size) != 0                                                      \
        ? (((__allocaComputeSize(size) <= (__ALLOCA_THRESHOLD + __ALLOCA_MARKER_SIZE))   \
            ? __markAlloca(alloca(__allocaComputeSize(size)), __ALLOCA_STACK_MARKER)     \
            : __markAlloca(malloc(__allocaComputeSize(size)), __ALLOCA_HEAP_MARKER)))    \
        : reinterpret_cast<void*>(NULL))

#endif

inline void _freea(void *ptr)
{
    if (ptr)
    {
        ptr = reinterpret_cast<char*>(ptr) - __ALLOCA_MARKER_SIZE;
        unsigned int allocaMarker = *reinterpret_cast<unsigned int*>(ptr);
        if (allocaMarker == __ALLOCA_HEAP_MARKER)
        {
            free(ptr);
        }
        else
        {
            assert((allocaMarker == __ALLOCA_STACK_MARKER) && "Corrupted pointer passed to _freea()");
        }
    }
}

#endif
