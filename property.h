#pragma once

#include <type_traits>

#define PROPERTY(TYPE, NAME)                                                                    \
public:                                                                                         \
  template <class T,                                                                            \
            class = std::enable_if_t <std::is_same_v < std::decay_t<T>, TYPE >>                 \
            >                                                                                   \
  inline void Set##NAME(T&& name) noexcept(std::is_nothrow_assignable<TYPE&, T>::value)         \
  {                                                                                             \
    m_##NAME = std::forward<T>(name);                                                           \
  }                                                                                             \
  inline TYPE NAME() const                                                                      \
  {                                                                                             \
    return m_##NAME;                                                                            \
  }                                                                                             \
private:                                                                                        \
  TYPE m_##NAME;                                                                                \

