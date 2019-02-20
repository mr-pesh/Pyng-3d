#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/vector_query.hpp>

#include <Utils/Global.h>

#include <limits>

namespace std
{
    template <glm::length_t L, typename T, glm::qualifier Q>
    constexpr auto begin(glm::vec<L, T, Q> &vec) noexcept
    {
        return glm::value_ptr(vec);
    }

    template <glm::length_t L, typename T, glm::qualifier Q>
    constexpr auto begin(const glm::vec<L, T, Q> &vec) noexcept
    {
        return glm::value_ptr(vec);
    }

    template <glm::length_t L, typename T, glm::qualifier Q>
    constexpr auto end(glm::vec<L, T, Q> &vec) noexcept
    {
        return glm::value_ptr(vec) + vec.length();
    }

    template <glm::length_t L, typename T, glm::qualifier Q>
    constexpr auto end(const glm::vec<L, T, Q> &vec) noexcept
    {
        return glm::value_ptr(vec) + vec.length();
    }
}

namespace
{
    template <bool isFloatingPoint>
    struct GLMVectorGeometryMapper;

    template <>
    struct GLMVectorGeometryMapper<true>
    {
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline auto Angle(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, T1, Q>(glm::angle(vector1, vector2));
            } else {
                return glm::vec<L, T1, Q>(glm::angle(vector1, glm::vec<L, float_t, Q>(vector2)));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline auto Normalize(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::normalize(vec);
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool IsNormalized(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::isNormalized(vec, std::numeric_limits<T>::epsilon());
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline auto CrossProduct(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::cross(vector1, vector2);
            } else {
                return glm::cross(vector1, glm::vec<L, float_t, Q>(vector2));
            }
        }
    };

    template <>
    struct GLMVectorGeometryMapper<false>
    {
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline auto Angle(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, float_t, Q>(glm::angle(glm::vec<L, float_t, Q>(vector1), vector2));
            } else {
                return glm::vec<L, float_t, Q>(glm::angle(glm::vec<L, float_t, Q>(vector1), glm::vec<L, float_t, Q>(vector2)));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline auto Normalize(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::normalize(glm::vec<L, float_t, Q>(vec));
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool IsNormalized(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::isNormalized(glm::vec<L, float_t, Q>(vec), std::numeric_limits<float_t>::epsilon());
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline auto CrossProduct(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::cross(glm::vec<L, float_t, Q>(vector1), vector2);
            } else {
                return glm::cross(glm::vec<L, float_t, Q>(vector1), glm::vec<L, float_t, Q>(vector2));
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
        static __always_inline bool Greater(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThan(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::greaterThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline bool GreaterOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThanEqual(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::greaterThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline bool Equal(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return vec1 == GLMStoreInt(vec2);
            } else {
                return vec1 == vec2;
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline bool Less(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThan(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::lessThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline bool LessOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThanEqual(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::lessThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline bool NotEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
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
        static __always_inline bool Greater(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThan(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::greaterThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline bool GreaterOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThanEqual(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::greaterThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline bool Equal(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::vec<L, float_t, Q>(vec1) == vec2;
            } else {
                return vec1 == vec2;
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline bool Less(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThan(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::lessThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline bool LessOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThanEqual(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::lessThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static __always_inline bool NotEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
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
 * Returns the absolute angle between vectors. Parameters have to be normalized.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline auto AngleBetweenNormals(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T1>>::Angle(vector1, vector2);
}

/**
 * Computes the radian angle between two vectors.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline auto AngleBetweenVectors(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    const bool v1 = IsNormalized(vector1);
    const bool v2 = IsNormalized(vector2);

    if (UNLIKELY(v1 && v2)) {
        return AngleBetweenNormals(vector1, vector2);
    } else {
        return v1 ?
               AngleBetweenNormals(vector1, Normalize(vector2)):
               AngleBetweenNormals(Normalize(vector1), vector2);
    }
}

/**
 * Computes the cross product between two vectors.
 */
template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline auto CrossProduct(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryMapper<std::is_floating_point_v<T1>>::CrossProduct(vector1, vector2);
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
inline bool operator>(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorComparisonMapper<std::is_floating_point_v<T1>>::Greater(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator>=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorComparisonMapper<std::is_floating_point_v<T1>>::GreaterOrEqual(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator<(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorComparisonMapper<std::is_floating_point_v<T1>>::Less(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator<=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorComparisonMapper<std::is_floating_point_v<T1>>::LessOrEqual(vector1, vector2);
}
