namespace glm
{
    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<L, T, Q> clampLength(const vec<L, T, Q> &source, float &min, float &max) noexcept
    {
        return clampLength(source, vec<L, T, Q>(min), vec<L, T, Q>(max));
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<2, T, Q> clampLength(const vec<2, T, Q> &source, const vec<2, T, Q> &min, const vec<2, T, Q> &max) noexcept
    {
        using glm_vec2 = ::glm::vec<2, T, Q>;

        assert(max >= min);
        assert(min >= glm_vec2(0));
        assert(max >= glm_vec2(0));

        assert(min.y == min.x);
        assert(max.y == max.x);

        glm_vec2 len2(length2(source));
        glm_vec2 invLen = inversesqrt(len2);

        auto sMask = equal(isinf(len2), equal(len2, glm_vec2(0)));
        glm_vec2 length = mix(len2, (len2 * invLen), sMask);

        auto cMin = lessThan(length, min);
        auto cMax = greaterThan(length, max);

        glm_vec2 result = mix(len2, (source * invLen), sMask) * mix(mix(length, max, cMax), min, cMin);

        return mix(result, source, equal(cMax, cMin));
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<3, T, Q> clampLength(const vec<3, T, Q> &source, const vec<3, T, Q> &min, const vec<3, T, Q> &max) noexcept
    {
        using glm_vec3 = ::glm::vec<3, T, Q>;

        assert(max >= min);
        assert(min >= glm_vec3(0));
        assert(max >= glm_vec3(0));

        assert((min.y == min.x) && (min.z == min.x));
        assert((max.y == max.x) && (max.z == max.x));

        glm_vec3 len2(length2(source));
        glm_vec3 invLen = inversesqrt(len2);

        auto sMask = equal(isinf(len2), equal(len2, glm_vec3(0)));
        glm_vec3 length = mix(len2, (len2 * invLen), sMask);

        auto cMin = lessThan(length, min);
        auto cMax = greaterThan(length, max);

        glm_vec3 result = mix(len2, (source * invLen), sMask) * mix(mix(length, max, cMax), min, cMin);

        return mix(result, source, equal(cMax, cMin));
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<4, T, Q> clampLength(const vec<4, T, Q> &source, const vec<4, T, Q> &min, const vec<4, T, Q> &max) noexcept
    {
        using glm_vec4 = ::glm::vec<4, T, Q>;

        assert(max >= min);
        assert(min >= glm_vec4(0));
        assert(max >= glm_vec4(0));

        assert((min.y == min.x) && (min.z == min.x) && (min.w == min.x));
        assert((max.y == max.x) && (max.z == max.x) && (max.w == max.x));

        glm_vec4 len2(length2(source));
        glm_vec4 invLen = inversesqrt(len2);

        auto sMask = equal(isinf(len2), equal(len2, glm_vec4(0)));
        glm_vec4 length = mix(len2, len2 * invLen, sMask);

        auto cMax = greaterThan(length, max);
        auto cMin = lessThan(length, min);

        glm_vec4 result = mix(len2, source * invLen, sMask) * mix(mix(length, max, cMax), min, cMin);

        return mix(result, source, equal(cMax, cMin));
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<2, T, Q> orthogonal(const vec<2, T, Q> &source) noexcept
    {
        return vec<2, T, Q>(-source.y, source.x);
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<3, T, Q> orthogonal(const vec<3, T, Q> &source) noexcept
    {
        using glm_vec3 = ::glm::vec<3, T, Q>;

        const glm_vec3 zero(0);

        glm_vec3 ZZZ = ::glm::zzz(source);
        glm_vec3 YZY = ::glm::yzy(source);
        glm_vec3 nSource = -source;

        glm_vec3 S = YZY + ZZZ;
        glm_vec3 D = YZY - ZZZ;

        auto sMask = equal(lessThan(ZZZ, zero), lessThan(YZY, zero));

        return mix(glm_vec3(D.x, source.x, source.x), glm_vec3(S.x, nSource.x, nSource.x), sMask);
    }

    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<4, T, Q> orthogonal(const vec<4, T, Q> &source) noexcept
    {
        return vec<4, T, Q>(source.z, source.w, -source.x, -source.y);
    }
}
