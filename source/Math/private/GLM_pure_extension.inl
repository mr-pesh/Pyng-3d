namespace glm::extensions
{
    using ::glm::vec;

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<L, T, Q> clampLength(const vec<L, T, Q> &source, T min, T max) noexcept
    {
        return clampLength(source, vec<L, T, Q>(min), vec<L, T, Q>(max));
    }

    template <length_t L, typename T1, typename T2, typename T3, typename T4, qualifier Q>
    GLM_FUNC_QUALIFIER vec<L, T4, Q> clampLength(const vec<L, T1, Q> &source, const vec<L, T2, Q> &min, const vec<L, T3, Q> &max) noexcept
    {
        using glm_vec = vec<L, T4, Q>;

        glm_vec len2(::glm::length2(source));
        glm_vec invLen = inversesqrt(len2);

        auto sMask = equal(isinf(len2), equal(len2, glm_vec(0)));
        glm_vec length = mix(len2, (len2 * invLen), sMask);

        auto cMin = lessThan(length, min);
        auto cMax = greaterThan(length, max);

        glm_vec result = mix(len2, (source * invLen), sMask) * mix(mix(length, max, cMax), min, cMin);

        return mix(result, source, equal(cMax, cMin));
    }

    template <length_t L, typename T1, typename T2, qualifier Q>
    GLM_FUNC_QUALIFIER bool inBounds(const vec<L, T1, Q> &vec1, const vec<L, T2, Q> &vec2) noexcept
    {
        return all(lessThanEqual(vec1, vec2)) && all(greaterThanEqual(vec1, -vec2));
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<2, T, Q> orthogonal(const vec<2, T, Q> &source) noexcept
    {
        return { -source.y, source.x };
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<3, T, Q> orthogonal(const vec<3, T, Q> &source) noexcept
    {
        using glm_vec = vec<3, T, Q>;

        const glm_vec zero(0);

        glm_vec zzz = ::glm::zzz(source);
        glm_vec yzy = ::glm::yzy(source);
        glm_vec nSource = -source;

        glm_vec S = yzy + zzz;
        glm_vec D = yzy - zzz;

        auto sMask = equal(lessThan(zzz, zero), lessThan(yzy, zero));

        return mix(glm_vec(D.x, source.x, source.x), glm_vec(S.x, nSource.x, nSource.x), sMask);
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<4, T, Q> orthogonal(const vec<4, T, Q> &source) noexcept
    {
        return { source.z, source.w, -source.x, -source.y };
    }

    template <length_t L, typename T1, typename T2, typename T3, qualifier Q>
    GLM_FUNC_QUALIFIER vec<L, T3, Q> vectorAngle(const vec<L, T1, Q> &vec1, const vec<L, T2, Q> &vec2) noexcept
    {
        using glm_vec = vec<L, T3, Q>;
        return acos(clamp(dot(vec1, vec2) * (reciprocalLength(vec1) * reciprocalLength(vec2)), glm_vec(-1), glm_vec(1)));
    }
}
