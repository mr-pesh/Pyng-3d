namespace
{
    template <bool isFloatingPoint>
    struct GLMVectorRelationalHelper;

    template <>
    struct GLMVectorRelationalHelper<true>
    {
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool Greater(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThan(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::greaterThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool GreaterOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThanEqual(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::greaterThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool Equal(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::operator==(vec1, glm::vec<L, float_t, Q>(vec2));
            } else {
                return glm::operator==(vec1, vec2);
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool Less(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThan(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::lessThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool LessOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThanEqual(vec1, glm::vec<L, float_t, Q>(vec2)));
            } else {
                return glm::all(glm::lessThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool NotEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (!std::is_floating_point_v<T2>) {
                return glm::operator!=(vec1, glm::vec<L, float_t, Q>(vec2));
            } else {
                return glm::operator!=(vec1, vec2);
            }
        }
    };

    template <>
    struct GLMVectorRelationalHelper<false>
    {
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool Greater(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThan(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::greaterThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool GreaterOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::greaterThanEqual(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::greaterThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool Equal(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::operator==(glm::vec<L, float_t, Q>(vec1), vec2);
            } else {
                return glm::operator==(vec1, vec2);
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool Less(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThan(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::lessThan(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool LessOrEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::all(glm::lessThanEqual(glm::vec<L, float_t, Q>(vec1), vec2));
            } else {
                return glm::all(glm::lessThanEqual(vec1, vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool NotEqual(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::operator!=(glm::vec<L, float_t, Q>(vec1), vec2);
            } else {
                return glm::operator!=(vec1, vec2);
            }
        }
    };
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorRelationalHelper<std::is_floating_point_v<T1>>::Equal(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorRelationalHelper<std::is_floating_point_v<T1>>::NotEqual(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator>(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorRelationalHelper<std::is_floating_point_v<T1>>::Greater(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator>=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorRelationalHelper<std::is_floating_point_v<T1>>::GreaterOrEqual(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator<(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorRelationalHelper<std::is_floating_point_v<T1>>::Less(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator<=(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorRelationalHelper<std::is_floating_point_v<T1>>::LessOrEqual(vector1, vector2);
}
