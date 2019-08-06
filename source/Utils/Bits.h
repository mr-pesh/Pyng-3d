#pragma once

#include <Utils/Global.h>
#include <type_traits>

/**
 * @brief Count the number of 1 bits in 16-, 32- or 64-bit [unsigned] integer.
 * @remark The result of the function can be expressed with following code:
 * @code
 * int count = 0
 * for (; value > 0; value >>= 1) {
 *     if (value & 1) {
 *         count++;
 *     }
 * }
 * return count;
 * @endcode
 */
template <typename T>
FORCE_INLINE int popcount(T value) noexcept;

/**
 * @brief Check bit of \param value at \param index and return it's value.
 * @remark The result of the function can be expressed with following code: @code 
 * return (value & (1 << index))
 * @endcode
 * @warning Garantees to generate X86 **BT** instruction
 */
template <typename T, typename Size>
FORCE_INLINE bool getBit(T const& value, Size index) noexcept;

/**
 * @brief Set bit of \param value at \param index to 1.
 * @remark The result of the function can be expressed with following code: @code
 * value |= (1 << index);
 * @endcode
 * @warning Garantees to generate X86 **BTS** instruction
 */
template <typename T, typename Size>
FORCE_INLINE void setBit(T& value, Size index) noexcept;

/**
 * @brief Set bit of \param value at \param index to 0.
 * @remark The result of the function can be expressed with following code: @code
 * value &= ~(1 << index);
 * @endcode
 * @warning Garantees to generate X86 **BTR** instruction
 */
template <typename T, typename Size>
FORCE_INLINE void clearBit(T& value, Size index) noexcept;

/**
 * @brief Set bit of \param value at \param index to its complement.
 * @remark The result of the function can be expressed with following code: @code
 * getBit(value, index) ? clearBit(value, index) : setBit(value, index);
 * @endcode
 * @warning Garantees to generate X86 **BTC** instruction
 */
template <typename T, typename Size>
FORCE_INLINE void flipBit(T& value, Size index) noexcept;

#ifdef _MSC_VER
# include "private/MSVC/bitops.inl"
#else
# include "private/UNIX/bitops.inl"
#endif
