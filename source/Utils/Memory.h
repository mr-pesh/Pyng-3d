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
# define _ALLOCA_MARKER_SIZE 16
#else
# define _ALLOCA_MARKER_SIZE 8
#endif

#define _ALLOCA_THRESHOLD 1024

static constexpr unsigned int _ALLOCA_HEAP_MARKER = 0xDDDD;
static constexpr unsigned int _ALLOCA_STACK_MARKER = 0xCCCC;

inline void* __markAlloca(void *ptr, unsigned int allocaMarker)
{
    if (ptr)
    {
        *reinterpret_cast<unsigned int*>(ptr) = allocaMarker;
        ptr = reinterpret_cast<char*>(ptr) + _ALLOCA_MARKER_SIZE;
    }
    return ptr;
}

inline size_t __allocaComputeSize(size_t size)
{
    size_t markedSize = size + _ALLOCA_MARKER_SIZE;
    return markedSize > size ? markedSize : 0;
}


#ifndef NDEBUG

#define _malloca(size)                                                           \
    (__allocaComputeSize(size) != 0                                              \
        ? __markAlloca(malloc(__allocaComputeSize(size)), _ALLOCA_HEAP_MARKER)   \
        : reinterpret_cast<void*>(NULL))

#else

#define _malloca(size)                                                                 \
    (__allocaComputeSize(size) != 0                                                    \
        ? (((__allocaComputeSize(size) <= (_ALLOCA_THRESHOLD + _ALLOCA_MARKER_SIZE))   \
            ? __markAlloca(alloca(__allocaComputeSize(size)), _ALLOCA_STACK_MARKER)    \
            : __markAlloca(malloc(__allocaComputeSize(size)), _ALLOCA_HEAP_MARKER)))   \
        : reinterpret_cast<void*>(NULL))

#endif

inline void _freea(void *ptr)
{
    if (ptr)
    {
        ptr = reinterpret_cast<char*>(ptr) - _ALLOCA_MARKER_SIZE;
        unsigned int allocaMarker = *reinterpret_cast<unsigned int*>(ptr);
        if (allocaMarker == _ALLOCA_HEAP_MARKER)
        {
            free(ptr);
        }
        else
        {
            assert((allocaMarker == _ALLOCA_STACK_MARKER) && "Corrupted pointer passed to _freea()");
        }
    }
}

#endif