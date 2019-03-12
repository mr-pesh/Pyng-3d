namespace glm
{
    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER auto vectorAngle(const vec<L, T, Q> &vec1, const vec<L, T, Q> &vec2) noexcept
    {
        using glm_vec = ::glm::vec<L, T, Q>;
        return acos(clamp(extensions::dot(vec1, vec2) * (extensions::reciprocalLength(vec1) * extensions::reciprocalLength(vec2)), glm_vec(-1), glm_vec(1)));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<L, T, Q> clampLength(const vec<L, T, Q> &source, float min, float max) noexcept
    {
        return clampLength(source, vec<L, T, Q>(min), vec<L, T, Q>(max));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<L, T, Q> clampLength(const vec<L, T, Q> &source, const vec<L, T, Q> &min, const vec<L, T, Q> &max) noexcept
    {
        using glm_vec = ::glm::vec<L, T, Q>;

        glm_vec len2(length2(source));
        glm_vec invLen = inversesqrt(len2);

        auto sMask = equal(isinf(len2), equal(len2, glm_vec(0)));
        glm_vec length = mix(len2, (len2 * invLen), sMask);

        auto cMin = lessThan(length, min);
        auto cMax = greaterThan(length, max);

        glm_vec result = mix(len2, (source * invLen), sMask) * mix(mix(length, max, cMax), min, cMin);

        return mix(result, source, equal(cMax, cMin));
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<2, T, Q> orthogonal(const vec<2, T, Q> &source) noexcept
    {
        return { -source.y, source.x };
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<3, T, Q> orthogonal(const vec<3, T, Q> &source) noexcept
    {
        using glm_vec = ::glm::vec<3, T, Q>;

        const glm_vec zero(0);

        glm_vec ZZZ = ::glm::zzz(source);
        glm_vec YZY = ::glm::yzy(source);
        glm_vec nSource = -source;

        glm_vec S = YZY + ZZZ;
        glm_vec D = YZY - ZZZ;

        auto sMask = equal(lessThan(ZZZ, zero), lessThan(YZY, zero));

        return mix(glm_vec(D.x, source.x, source.x), glm_vec(S.x, nSource.x, nSource.x), sMask);
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<4, T, Q> orthogonal(const vec<4, T, Q> &source) noexcept
    {
        return { source.z, source.w, -source.x, -source.y };
    }
}
