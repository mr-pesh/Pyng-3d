#include <glm/gtc/type_ptr.hpp>

namespace std
{
    template <typename T>
    constexpr auto begin(T& glm_type) noexcept
    {
        return glm::value_ptr(glm_type);
    }

    template <typename T>
    constexpr auto begin(const T& glm_type) noexcept
    {
        return glm::value_ptr(glm_type);
    }

    template <typename T>
    constexpr auto end(T& glm_type) noexcept
    {
        return glm::value_ptr(glm_type) + glm_type.length();
    }

    template <typename T>
    constexpr auto end(const T& glm_type) noexcept
    {
        return glm::value_ptr(glm_type) + glm_type.length();
    }
}

namespace
{
    template <bool isFloatingPoint>
    struct GLMVectorGeometryMapper;

    template <>
    struct GLMVectorGeometryMapper<true>
    {
        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline auto Normalize(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::normalize(vec);
        }
    };

    template <>
    struct GLMVectorGeometryMapper<false>
    {
        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline auto Normalize(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::normalize(glm::vec<L, float_t, Q>(vec));
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
                return vec1 != GLMStoreInt(vec2);
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
