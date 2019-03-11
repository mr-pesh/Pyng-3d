#pragma once

#include "GLM_Extensions.h"

#include <limits>


/**
 * Tests wether two vectors are equal. The result of the function can be expressed with following code:
 * <code>(vector1.x == vector2.x) && (vector1.y == vector2.y) [&& (vector1.z == vector2.z) [&& (vector1.w == vector2.w)]]</code>
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;

/**
 * Tests wether two vectors are not equal. The result of the function can be expressed with following code:
 * <code>(vector1.x != vector2.x) || (vector1.y != vector2.y) [|| (vector1.z != vector2.z) [|| (vector1.w != vector2.w)]]</code>
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;

/**
 * Tests wether one vector is greater than another vector. The result of the function can be expressed with following code:
 * <code>(vector1.x > vector2.x) && (vector1.y > vector2.y) [&& (vector1.z > vector2.z) [&& (vector1.w > vector2.w)]]</code>
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator>(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;

/**
 * Tests wether one vector is greater-than- or equal-to another vector. The result of the function can be expressed with following code:
 * <code>(vector1.x >= vector2.x) && (vector1.y >= vector2.y) [&& (vector1.z >= vector2.z) [&& (vector1.w >= vector2.w)]]</code>
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator>=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;

/**
 * Tests wether one vector is less than another vector. The result of the function can be expressed with following code:
 * <code>(vector1.x < vector2.x) && (vector1.y < vector2.y) [&& (vector1.z < vector2.z) [&& (vector1.w < vector2.w)]]</code>
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator<(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;

/**
 * Tests wether one vector is less-than- or equal-to another vector. The result of the function can be expressed with following code:
 * <code>(vector1.x <= vector2.x) && (vector1.y <= vector2.y) [&& (vector1.z <= vector2.z) [&& (vector1.w <= vector2.w)]]</code>
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator<=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;


#include "GLM_vector_relational.inl"


/**
 * Computes the radian angle between two normalized vectors.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto AngleBetweenNormals(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;

/**
 * Computes the radian angle between two vectors.
 * If vector1 and vector2 are normalized vectors, it is faster to use AngleBetweenNormals.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto AngleBetweenVectors(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;

/**
 * Clamps the length of a vector to a given range.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto ClampLength(const glm::vec<L, T, Q> &vector, float min, float max) noexcept;

/**
 * Computes the cross product between two vectors.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto CrossProduct(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;

/**
 * Computes the distance between vector1 and vector2, i.e., Length(vector1 - vector2).
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Distance(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;

/**
 * Computes the dot product between vectors.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto DotProduct(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept;

/**
 * Flips the surface-normal (if needed) to face in a direction opposite to vector.
 */
template <glm::length_t L, typename T1, typename T2, typename T3 = std::common_type_t<T1, T2, float_t>, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Faceforward(const glm::vec<L, T1, Q> &normal, const glm::vec<L, T2, Q> &vector, const glm::vec<L, T3, Q> &nref) noexcept;

/**
 * Check if a vector is normalized.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER bool IsNormalized(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * Flips the surface-normal (if needed) to face in a direction opposite to vector.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER bool InBounds(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &bounds) noexcept;

/**
 * Computes the length of a vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Length(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * Computes the square length of a vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto LengthSq(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * Computes the minimum distance between a line and a point.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto LinePointDistance(const glm::vec<L, T1, Q> &linePoint1, const glm::vec<L, T1, Q> &linePoint2, const glm::vec<L, T2, Q> &point) noexcept;

/**
 * Returns the normalized version of a vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Normalize(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * Computes a vector perpendicular to a given vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto OrthogonalVector(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * Computes the reciprocal of the length of a vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto ReciprocalLength(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * Reflects an incident vector across a normal vector.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Reflect(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &normal) noexcept;

/**
 * Refracts an incident vector across a normal vector.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Refract(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &normal, std::common_type_t<T1, T2, float_t> refractionIndex) noexcept;

/**
 * Retrieve the X component of a Vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetX(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * Retrieve the Y component of a Vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetY(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * Retrieve the Z component of a Vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetZ(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * Retrieve the W component of a Vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR T VectorGetW(const glm::vec<L, T, Q> &vector) noexcept;

/**
 * Retrieve the value of one of the four components of a Vector by index.
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

