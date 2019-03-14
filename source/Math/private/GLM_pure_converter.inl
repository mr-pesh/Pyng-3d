namespace glm::extensions
{
    using ::glm::vec;

    template <length_t L, typename T1, typename T2, qualifier Q>
    GLM_FUNC_QUALIFIER auto angle(const vec<L, T1, Q> &vec1, const vec<L, T2, Q> &vec2) noexcept
    {
        return vec<L, std::common_type_t<T1, T2>, Q>(::glm::angle(vec1, vec2));
    }

    template <length_t L, typename T1, typename T2, qualifier Q>
    GLM_FUNC_QUALIFIER auto distance(const vec<L, T1, Q> &vec1, const vec<L, T2, Q> &vec2) noexcept
    {
        return vec<L, std::common_type_t<T1, T2>, Q>(::glm::distance(vec1, vec2));
    }

    template <length_t L, typename T1, typename T2, qualifier Q>
    GLM_FUNC_QUALIFIER auto dot(const vec<L, T1, Q> &vec1, const vec<L, T2, Q> &vec2) noexcept
    {
        return vec<L, std::common_type_t<T1, T2>, Q>(::glm::dot(vec1, vec2));
    }

    template <length_t L, typename T1, typename T2, qualifier Q>
    GLM_FUNC_QUALIFIER bool inBounds(const vec<L, T1, Q> &vec1, const vec<L, T2, Q> &vec2) noexcept
    {
        return all(lessThanEqual(vec1, vec2)) && all(greaterThanEqual(vec1, -vec2));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER auto length(const vec<L, T, Q> &vec1) noexcept
    {
        return vec<L, T, Q>(::glm::length(vec1));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER auto length2(const vec<L, T, Q> &vec1) noexcept
    {
        return vec<L, T, Q>(::glm::length2(vec1));
    }

    template <length_t L, typename T1, typename T2, qualifier Q>
    GLM_FUNC_QUALIFIER auto linePointDistance(const vec<L, T1, Q> &vec1, const vec<L, T1, Q> &vec2, const vec<L, T2, Q> &vec3) noexcept
    {
        return vec<L, std::common_type_t<T1, T2>, Q>(::glm::distance(closestPointOnLine(vec3, vec1, vec2), vec3));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER auto reciprocalLength(const vec<L, T, Q> &vec1) noexcept
    {
        return vec<L, T, Q>(1.f / ::glm::length(vec1));
    }
}
