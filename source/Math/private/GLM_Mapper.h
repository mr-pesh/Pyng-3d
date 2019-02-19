#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>

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

//namespace VectorAngle
//{
//    /// <summary>Computes the radian angle between two 2-, 3- or 4D vectors.</summary>
//    template <class V1, class V2>
//    inline auto AngleBetweenVectors(V1 &&vector1, V2 &&vector2) noexcept
//    {
//        return Vector_Geometry<std::decay_t<V1>>::AngleBetweenVectors(std::forward<V1>(vector1), std::forward<V2>(vector2));
//    }

//    /// <summary>Computes the radian angle between two normalized 2-, 3- or 4D vectors.</summary>
//    template <class V1, class V2>
//    inline XMVECTOR AngleBetweenNormals(V1 &&vector1, V2 &&vector2) noexcept
//    {
//        return Vector_Geometry<std::decay_t<V1>>::AngleBetweenNormals(std::forward<V1>(vector1), std::forward<V2>(vector2));
//    }
//}

template <glm::length_t L, typename T, glm::qualifier Q>
static __always_inline auto GLMStoreInt(const glm::vec<L, T, Q> &vec) noexcept -> decltype(auto)
{
    glm::vec<L, float_t, Q> result;

    std::transform(std::begin(vec), std::end(vec), std::begin(result), [](const T value)
    {
        return std::trunc(value);
    });

    return result;
}

namespace
{
    template <typename T>
    struct GLMGeometryAdapter;

    template <>
    struct GLMGeometryAdapter<float_t>
    {
        template <glm::length_t L, glm::qualifier Q>
        static inline glm::vec<L, float_t, Q> Normalize(const glm::vec<L, float_t, Q> &vec) noexcept
        {
            return glm::normalize(vec);
        }
    };

    template <>
    struct GLMGeometryAdapter<double_t>
    {
        template <glm::length_t L, glm::qualifier Q>
        static inline glm::vec<L, double_t, Q> Normalize(const glm::vec<L, double_t, Q> &vec) noexcept
        {
            return glm::normalize(vec);
        }
    };

    template <>
    struct GLMGeometryAdapter<int32_t>
    {
        template <glm::length_t L, glm::qualifier Q>
        static inline glm::vec<L, float_t, Q> Normalize(const glm::vec<L, int32_t, Q> &vec) noexcept
        {
            return glm::normalize(GLMStoreInt(vec));
        }
    };

    template <>
    struct GLMGeometryAdapter<uint32_t>
    {
        template <glm::length_t L, glm::qualifier Q>
        static inline glm::vec<L, float_t, Q> Normalize(const glm::vec<L, uint32_t, Q> &vec) noexcept
        {
            return glm::normalize(GLMStoreInt(vec));
        }
    };
}

namespace
{
    template <typename T>
    struct GLMComparisonAdapter;

    template <>
    struct GLMComparisonAdapter<float_t>
    {
        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Greater(const glm::vec<L, float_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return glm::all(glm::greaterThan(vec1, GLMStoreInt(vec2)));
            } else {
                return glm::all(glm::greaterThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool GreaterOrEqual(const glm::vec<L, float_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return glm::all(glm::greaterThanEqual(vec1, GLMStoreInt(vec2)));
            } else {
                return glm::all(glm::greaterThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Equal(const glm::vec<L, float_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return vec1 == GLMStoreInt(vec2);
            } else {
                return vec1 == vec2;
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Less(const glm::vec<L, float_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return glm::all(glm::lessThan(vec1, GLMStoreInt(vec2)));
            } else {
                return glm::all(glm::lessThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool LessOrEqual(const glm::vec<L, float_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return glm::all(glm::lessThanEqual(vec1, GLMStoreInt(vec2)));
            } else {
                return glm::all(glm::lessThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool NotEqual(const glm::vec<L, float_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return vec1 != GLMStoreInt(vec2);
            } else {
                return vec1 != vec2;
            }
        }
    };

    template <>
    struct GLMComparisonAdapter<double_t>
    {
        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Greater(const glm::vec<L, double_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return glm::all(glm::greaterThan(vec1, GLMStoreInt(vec2)));
            } else {
                return glm::all(glm::greaterThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool GreaterOrEqual(const glm::vec<L, double_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return glm::all(glm::greaterThanEqual(vec1, GLMStoreInt(vec2)));
            } else {
                return glm::all(glm::greaterThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Equal(const glm::vec<L, double_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return vec1 == GLMStoreInt(vec2);
            } else {
                return vec1 == vec2;
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Less(const glm::vec<L, double_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return glm::all(glm::lessThan(vec1, GLMStoreInt(vec2)));
            } else {
                return glm::all(glm::lessThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool LessOrEqual(const glm::vec<L, double_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return glm::all(glm::lessThanEqual(vec1, GLMStoreInt(vec2)));
            } else {
                return glm::all(glm::lessThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool NotEqual(const glm::vec<L, double_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<int32_t,T> || std::is_same_v<uint32_t,T>) {
                return vec1 != GLMStoreInt(vec2);
            } else {
                return vec1 != vec2;
            }
        }
    };

    template <>
    struct GLMComparisonAdapter<int32_t>
    {
        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Greater(const glm::vec<L, int32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return glm::all(glm::greaterThan(GLMStoreInt(vec1), vec2));
            } else {
                return glm::all(glm::greaterThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool GreaterOrEqual(const glm::vec<L, int32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return glm::all(glm::greaterThanEqual(GLMStoreInt(vec1), vec2));
            } else {
                return glm::all(glm::greaterThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Equal(const glm::vec<L, int32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return GLMStoreInt(vec1) == vec2;
            } else {
                return vec1 == vec2;
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Less(const glm::vec<L, int32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return glm::all(glm::lessThan(GLMStoreInt(vec1), vec2));
            } else {
                return glm::all(glm::lessThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool LessOrEqual(const glm::vec<L, int32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return glm::all(glm::lessThanEqual(GLMStoreInt(vec1), vec2));
            } else {
                return glm::all(glm::lessThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool NotEqual(const glm::vec<L, int32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return GLMStoreInt(vec1) != vec2;
            } else {
                return vec1 != vec2;
            }
        }
    };

    template <>
    struct GLMComparisonAdapter<uint32_t>
    {
        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Greater(const glm::vec<L, uint32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return glm::all(glm::greaterThan(GLMStoreInt(vec1), vec2));
            } else {
                return glm::all(glm::greaterThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool GreaterOrEqual(const glm::vec<L, uint32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return glm::all(glm::greaterThanEqual(GLMStoreInt(vec1), vec2));
            } else {
                return glm::all(glm::greaterThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Equal(const glm::vec<L, uint32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return GLMStoreInt(vec1) == vec2;
            } else {
                return vec1 == vec2;
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool Less(const glm::vec<L, uint32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return glm::all(glm::lessThan(GLMStoreInt(vec1), vec2));
            } else {
                return glm::all(glm::lessThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool LessOrEqual(const glm::vec<L, uint32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return glm::all(glm::lessThanEqual(GLMStoreInt(vec1), vec2));
            } else {
                return glm::all(glm::lessThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static __always_inline bool NotEqual(const glm::vec<L, uint32_t, Q> &vec1, const glm::vec<L, T, Q> &vec2) noexcept
        {
            if constexpr (std::is_same_v<float_t,T> || std::is_same_v<double_t,T>) {
                return GLMStoreInt(vec1) != vec2;
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
    return GLMGeometryAdapter<T>::Normalize(vector);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator==(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMComparisonAdapter<T1>::Equal(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator!=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMComparisonAdapter<T1>::NotEqual(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator>(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMComparisonAdapter<T1>::Greater(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator>=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMComparisonAdapter<T1>::GreaterOrEqual(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator<(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMComparisonAdapter<T1>::Less(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
inline bool operator<=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMComparisonAdapter<T1>::LessOrEqual(vector1, vector2);
}
