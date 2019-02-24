#define GLM_ENABLE_EXPERIMENTAL

#include <Utils/Global.h>

#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/vector_query.hpp>

#include <limits>

namespace
{
    template <bool isFloatingPoint>
    struct GLMVectorGeometryMapper;

    template <>
    struct GLMVectorGeometryMapper<true>
    {
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Angle(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, T1, Q>(glm::angle(vec1, vec2));
            } else {
                return glm::vec<L, T1, Q>(glm::angle(vec1, glm::vec<L, float_t, Q>(vec2)));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Distance(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, T1, Q>(glm::distance(vec1, vec2));
            }
            else {
                return glm::vec<L, T1, Q>(glm::distance(vec1, glm::vec<L, float_t, Q>(vec2)));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto DotProduct(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, T1, Q>(glm::dot(vec1, vec2));
            } else {
                return glm::vec<L, T1, Q>(glm::dot(vec1, glm::vec<L, float_t, Q>(vec2)));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Normalize(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::normalize(vec);
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        FORCE_INLINE_STATIC bool IsNormalized(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::isNormalized(vec, std::numeric_limits<T>::epsilon());
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto CrossProduct(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::cross(vec1, vec2);
            } else {
                return glm::cross(vec1, glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Length(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::length(vec);
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Reflect(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::reflect(vec1, vec2);
            }
            else {
                return glm::reflect(vec1, glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Refract(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2, std::common_type_t<T1, T2> index) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::refract(vec1, vec2, index);
            }
            else {
                return glm::refract(vec1, glm::vec<L, float_t, Q>(vec2), index);
            }
        }
    };

    template <>
    struct GLMVectorGeometryMapper<false>
    {
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Angle(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, float_t, Q>(glm::angle(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::vec<L, float_t, Q>(glm::angle(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2)));
            }
        }
        
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Distance(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, float_t, Q>(glm::distance(glm::vec<L, float_t, Q>(vec1), vec2));
            }
            else {
                return glm::vec<L, float_t, Q>(glm::distance(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2)));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto DotProduct(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, float_t, Q>(glm::dot(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::vec<L, float_t, Q>(glm::dot(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2)));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Normalize(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::normalize(glm::vec<L, float_t, Q>(vec));
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        FORCE_INLINE_STATIC bool IsNormalized(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::isNormalized(glm::vec<L, float_t, Q>(vec), std::numeric_limits<float_t>::epsilon());
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto CrossProduct(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::cross(glm::vec<L, float_t, Q>(vec1), vec2);
            } else {
                return glm::cross(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Length(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::length(glm::vec<L, float_t, Q>(vec));
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Reflect(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::reflect(glm::vec<L, float_t, Q>(vec1), vec2);
            }
            else {
                return glm::reflect(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC auto Refract(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2, std::common_type_t<T1, T2, float_t> index) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::refract(glm::vec<L, float_t, Q>(vec1), vec2, index);
            }
            else {
                return glm::refract(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2), index);
            }
        }
    };
}

namespace
{
    template <bool isFloatingPoint>
    struct GLMVectorComparisonMapper;

    template <>
    struct GLMVectorComparisonMapper<true>
    {
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool Greater(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThan(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::greaterThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool GreaterOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThanEqual(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::greaterThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool Equal(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return vec1 == GLMStoreInt(vec2);
            } else {
                return vec1 == vec2;
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool Less(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThan(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::lessThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool LessOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThanEqual(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::lessThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool NotEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return vec1 != glm::vec<L, float_t, Q>(vec2);
            } else {
                return vec1 != vec2;
            }
        }
    };

    template <>
    struct GLMVectorComparisonMapper<false>
    {
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool Greater(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThan(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::greaterThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool GreaterOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThanEqual(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::greaterThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool Equal(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, float_t, Q>(vec1) == vec2;
            } else {
                return vec1 == vec2;
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool Less(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThan(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::lessThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool LessOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThanEqual(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::lessThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        FORCE_INLINE_STATIC bool NotEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, float_t, Q>(vec1) != vec2;
            } else {
                return vec1 != vec2;
            }
        }
    };
}

/**
 * Returns the normalized version of a vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
inline auto Normalize(const glm::vec<L, T, Q> &vector) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T>>::Normalize(vector);
}

/**
 * Check if a vector is normalized.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
inline bool IsNormalized(const glm::vec<L, T, Q> &vector) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T>>::IsNormalized(vector);
}

/**
 * Computes the radian angle between two normalized vectors.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline auto AngleBetweenNormals(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T1>>::Angle(vector1, vector2);
}

/**
 * Computes the radian angle between two vectors.
 * If vector1 and vector2 are normalized vectors, it is faster to use AngleBetweenNormals.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline auto AngleBetweenVectors(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    const bool v1 = IsNormalized(vector1);
    const bool v2 = IsNormalized(vector2);

    if (UNLIKELY(v1 && v2)) {
        return AngleBetweenNormals(vector1, vector2);
    }
    if (v1 || v2) {
        return v1 ?
            AngleBetweenNormals(vector1, Normalize(vector2)):
            AngleBetweenNormals(Normalize(vector1), vector2);
    }
    return AngleBetweenNormals(Normalize(vector1), Normalize(vector2));
}

/**
 * Computes the distance between vector1 and vector2, i.e., Length(vector1 - vector2).
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline auto Distance(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T1>>::Distance(vector1, vector2);
}

/**
 * Computes the dot product between vectors.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline auto DotProduct(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T1>>::DotProduct(vector1, vector2);
}

/**
 * Computes the cross product between two vectors.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline auto CrossProduct(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T1>>::CrossProduct(vector1, vector2);
}

/**
 * Computes the length of a vector.
 */
template <glm::length_t L, typename T, glm::qualifier Q>
inline auto Length(const glm::vec<L, T, Q> &vector) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T>>::Length(vector);
}

/**
 * Reflects an incident vector across a normal vector.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline auto Reflect(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &normal) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T1>>::Reflect(vector, normal);
}

/**
 * Refracts an incident vector across a normal vector.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline auto Refract(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &normal, std::common_type_t<T1, T2, float_t> refractionIndex) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T1>>::Refract(vector, normal, refractionIndex);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator==(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorComparisonMapper<std::is_floating_point_v<T1>>::Equal(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator!=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorComparisonMapper<std::is_floating_point_v<T1>>::NotEqual(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator >(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorComparisonMapper<std::is_floating_point_v<T1>>::Greater(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator>=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorComparisonMapper<std::is_floating_point_v<T1>>::GreaterOrEqual(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator <(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorComparisonMapper<std::is_floating_point_v<T1>>::Less(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator<=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorComparisonMapper<std::is_floating_point_v<T1>>::LessOrEqual(vector1, vector2);
}
