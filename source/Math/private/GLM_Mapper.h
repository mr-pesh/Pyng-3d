#pragma once

#include "GLM_Extensions.h"
#include <limits>

/**
 * @brief Tests wether two vectors are equal.
 * @remark The result of the function can be expressed with following code: @code
 * (left.x == right.x) && (left.y == right.y) [&& (left.z == right.z) [&& (left.w == right.w)]] @endcode
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

/**
 * @brief Tests wether two vectors are not equal.
 * @remark The result of the function can be expressed with following code: @code
 * (left.x != right.x) || (left.y != right.y) [|| (left.z != right.z) [|| (left.w != right.w)]] @endcode
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

/**
 * @brief Tests wether one vector is greater than another vector.
 * @remark The result of the function can be expressed with following code: @code
 * (left.x > right.x) && (left.y > right.y) [&& (left.z > right.z) [&& (left.w > right.w)]] @endcode
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator>(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

/**
 * @brief Tests wether one vector is greater-than- or equal-to another vector.
 * @remark The result of the function can be expressed with following code: @code
 * (left.x >= right.x) && (left.y >= right.y) [&& (left.z >= right.z) [&& (left.w >= right.w)]] @endcode
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator>=(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

/**
 * @brief Tests wether one vector is less than another vector.
 * @remark The result of the function can be expressed with following code: @code
 * (left.x < right.x) && (left.y < right.y) [&& (left.z < right.z) [&& (left.w < right.w)]] @endcode
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator<(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

/**
 * @brief Tests wether one vector is less-than- or equal-to another vector.
 * @remark The result of the function can be expressed with following code: @code
 * (left.x <= right.x) && (left.y <= right.y) [&& (left.z <= right.z) [&& (left.w <= right.w)]] @endcode
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator<=(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

#include "GLM_vector_relational.inl"


/**
 * @brief Computes an angle between two normalized vectors.
 * @param left Normalized vector
 * @param right Normalized vector
 * @return The radian angle between \p left and \p right which is replicated into each of the components of a vector
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto AngleBetweenNormals(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

/**
 * @brief Computes an angle between two vectors.
 * @param left Vector
 * @param right Vector
 * @return The radian angle between \p left and \p right which is replicated into each of the components of a vector
 * @remark If \p left and \p right are normalized vectors, it is faster to use AngleBetweenNormals.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto AngleBetweenVectors(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

/**
 * @brief Clamps the length of a \p vector to a given range.
 * @param vector Vector
 * @param min Minimum clamp length
 * @param max Maximum clamp length
 * @return A vector with length that is clamped to the specified minimum and maximum.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto ClampLength(const glm::vec<L, T, Q> &vector, float min, float max) noexcept;

/**
 * @brief Computes the cross product between two vectors.
 * @param left Vector
 * @param right Vector
 * @return
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto CrossProduct(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

/**
 * @brief Computes the distance between \p left and \p right, i.e., \ref Length(\p left - \p right).
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Distance(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

/**
 * @brief Computes the dot product between vectors.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto DotProduct(const glm::vec<L, T1, Q> &left, const glm::vec<L, T2, Q> &right) noexcept;

/**
 * @brief Flips the surface-normal (if needed) to face in a direction opposite to vector.
 */
template <glm::length_t L, typename T1, typename T2, typename T3 = std::common_type_t<T1, T2, float_t>, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Faceforward(const glm::vec<L, T1, Q> &normal, const glm::vec<L, T2, Q> &vector, const glm::vec<L, T3, Q> &nref) noexcept;

/**
 * @brief Check if a vector is normalized.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER bool IsNormalized(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * @brief Tests whether the components of a given vector are within the specified bounds.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER bool InBounds(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &bounds) noexcept;

/**
 * @brief Computes the length of a vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Length(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * @brief Computes the square length of a vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto LengthSq(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * @brief Computes the minimum distance between a line and a point.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto LinePointDistance(const glm::vec<L, T1, Q> &linePoint1, const glm::vec<L, T1, Q> &linePoint2, const glm::vec<L, T2, Q> &point) noexcept;

/**
 * @brief Returns the normalized version of a vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Normalize(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * @brief Computes a vector perpendicular to a given vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto OrthogonalVector(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * @brief Computes the reciprocal of the length of a vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto ReciprocalLength(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * @brief Reflects an incident vector across a normal vector.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Reflect(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &normal) noexcept;

/**
 * @brief Refracts an incident vector across a normal vector.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Refract(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &normal, std::common_type_t<T1, T2, float_t> refractionIndex) noexcept;

/**
 * @brief Retrieve the X component of a Vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetX(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * @brief Retrieve the Y component of a Vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetY(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * @brief Retrieve the Z component of a Vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetZ(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * @brief Retrieve the W component of a Vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetW(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * @brief Retrieve the value of one of the four components of a Vector by index.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetByIndex(const glm::vec<L, T, Q> &vector, glm::length_t index) noexcept;


#include "GLM_vector_geometry.inl"


template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetX(const glm::vec<L, T, Q> &vector) noexcept
{
    return vector.x;
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetY(const glm::vec<L, T, Q> &vector) noexcept
{
    return vector.y;
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetZ(const glm::vec<L, T, Q> &vector) noexcept
{
    return vector.z;
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetW(const glm::vec<L, T, Q> &vector) noexcept
{
    return vector.w;
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetByIndex(const glm::vec<L, T, Q> &vector, glm::length_t index) noexcept
{
    return vector[index];
}

