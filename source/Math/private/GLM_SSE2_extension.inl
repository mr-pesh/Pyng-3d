namespace glm
{
    template <>
    GLM_FUNC_QUALIFIER glm_vec4 dot<2>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        glm_vec4 mul0 = _mm_mul_ps(vec1, vec2);
        glm_vec4 swp0 = _MM_PERMUTE_PS(mul0, _MM_SHUFFLE(1, 1, 1, 1));
        mul0 = _mm_add_ss(mul0, swp0);
        mul0 = _MM_PERMUTE_PS(mul0, _MM_SHUFFLE(0, 0, 0, 0));
        return mul0;
    }

    template <>
    GLM_FUNC_QUALIFIER glm_vec4 dot<3>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        glm_vec4 mul0 = _mm_mul_ps(vec1, vec2);
        glm_vec4 swp0 = _MM_PERMUTE_PS(mul0, _MM_SHUFFLE(2, 1, 2, 1));
        mul0 = _mm_add_ss(mul0, swp0);
        swp0 = _MM_PERMUTE_PS(swp0, _MM_SHUFFLE(1, 1, 1, 1));
        mul0 = _mm_add_ss(mul0, swp0);
        return _MM_PERMUTE_PS(mul0, _MM_SHUFFLE(0, 0, 0, 0));
    }

    template <>
    GLM_FUNC_QUALIFIER glm_vec4 dot<4>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        return glm_vec4_dot(vec1, vec2);
    }

    template <>
    GLM_FUNC_QUALIFIER bool greaterThanEqual<2>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        return ((_mm_movemask_ps(_mm_cmpge_ps(vec1, vec2)) & 3) == 3) != 0;
    }

    template <>
    GLM_FUNC_QUALIFIER bool greaterThanEqual<3>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        return ((_mm_movemask_ps(_mm_cmpge_ps(vec1, vec2)) & 7) == 7) != 0;
    }

    template <>
    GLM_FUNC_QUALIFIER bool greaterThanEqual<4>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        return (_mm_movemask_ps(_mm_cmpge_ps(vec1, vec2)) == 15) != 0;
    }

    GLM_FUNC_QUALIFIER glm_vec4 inversesqrt(glm_vec4 vec) noexcept
    {
        return _mm_div_ps(_mm_set1_ps(1.f), _mm_sqrt_ps(vec));
    }

    template <glm::length_t L>
    GLM_FUNC_QUALIFIER glm_vec4 length2(glm_vec4 vec) noexcept
    {
        return ::glm::dot<L>(vec, vec);
    }

    template <>
    GLM_FUNC_QUALIFIER glm_vec4 equal<int32_t>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        return _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(vec1), _mm_castps_si128(vec2)));
    }

    template <>
    GLM_FUNC_QUALIFIER glm_vec4 equal<float_t>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        return _mm_cmpeq_ps(vec1, vec2);
    }

    GLM_FUNC_QUALIFIER glm_vec4 greaterThan(glm_vec4 left, glm_vec4 right) noexcept
    {
        return _mm_cmpgt_ps(left, right);
    }

    GLM_FUNC_QUALIFIER glm_vec4 lessThan(glm_vec4 left, glm_vec4 right) noexcept
    {
        return _mm_cmplt_ps(left, right);
    }

    GLM_FUNC_QUALIFIER glm_vec4 mix(glm_vec4 left, glm_vec4 right, glm_vec4 control) noexcept
    {
        return _mm_or_ps(_mm_andnot_ps(control, left), _mm_and_ps(right, control));
    }

    template <glm::length_t L>
    GLM_FUNC_QUALIFIER glm_vec4 clampLength(glm_vec4 source, float min, float max) noexcept
    {
        return clampLength<L>(std::move(source), _mm_set1_ps(min), _mm_set1_ps(max));
    }

    template <>
    GLM_FUNC_QUALIFIER glm_vec4 clampLength<2>(glm_vec4 source, glm_vec4 min, glm_vec4 max) noexcept
    {
        glm_vec4 mul0 = _mm_mul_ps(source, source);
        glm_vec4 swp0 = _MM_PERMUTE_PS(mul0, _MM_SHUFFLE(1, 1, 1, 1));
        mul0 = _mm_div_ss(_mm_set1_ps(1.f), _mm_sqrt_ss(_mm_add_ss(mul0, swp0)));
        return _MM_PERMUTE_PS(mul0, _MM_SHUFFLE(0, 0, 0, 0));
    }

    template <>
    GLM_FUNC_QUALIFIER glm_vec4 clampLength<3>(glm_vec4 source, glm_vec4 min, glm_vec4 max) noexcept
    {
        assert(greaterThanEqual<3>(max, min));
        assert(greaterThanEqual<3>(max, _mm_setzero_ps()));
        assert(greaterThanEqual<3>(min, _mm_setzero_ps()));

        assert((glm_vec4_getY(min) == glm_vec4_getX(min)) && (glm_vec4_getZ(min) == glm_vec4_getX(min)));
        assert((glm_vec4_getY(max) == glm_vec4_getX(max)) && (glm_vec4_getZ(max) == glm_vec4_getX(max)));

        glm_vec4 len2 = length2<3>(source);
        glm_vec4 invLen = inversesqrt(len2);

        glm_vec4 sMask = equal<int>(equal<int>(len2, SSE2_INFINITY), equal(len2, _mm_setzero_ps()));
        glm_vec4 length = mix(len2, _mm_mul_ps(len2, invLen), sMask);

        glm_vec4 cMin = lessThan(length, min);
        glm_vec4 cMax = greaterThan(length, max);

        glm_vec4 result = _mm_mul_ps(
            mix(len2, _mm_mul_ps(source, invLen), sMask), mix(mix(length, max, cMax), min, cMin)
        );

        return mix(result, source, equal<int>(cMax, cMin));
    }

    template <>
    GLM_FUNC_QUALIFIER glm_vec4 clampLength<4>(glm_vec4 source, glm_vec4 min, glm_vec4 max) noexcept
    {
        assert(greaterThanEqual<4>(max, min));
        assert(greaterThanEqual<4>(min, _mm_setzero_ps()));
        assert(greaterThanEqual<4>(max, _mm_setzero_ps()));

        assert((glm_vec4_getY(min) == glm_vec4_getX(min)) && (glm_vec4_getZ(min) == glm_vec4_getX(min)) && (glm_vec4_getW(min) == glm_vec4_getX(min)));
        assert((glm_vec4_getY(max) == glm_vec4_getX(max)) && (glm_vec4_getZ(max) == glm_vec4_getX(max)) && (glm_vec4_getW(max) == glm_vec4_getX(max)));

        glm_vec4 len2 = length2<4>(source);
        glm_vec4 invLen = inversesqrt(len2);

        glm_vec4 sMask = equal<int>(equal<int>(len2, SSE2_INFINITY), equal(len2, _mm_setzero_ps()));
        glm_vec4 length = mix(len2, _mm_mul_ps(len2, invLen), sMask);

        glm_vec4 cMin = lessThan(length, min);
        glm_vec4 cMax = greaterThan(length, max);

        glm_vec4 result = _mm_mul_ps(
            mix(len2, _mm_mul_ps(source, invLen), sMask), mix(mix(length, max, cMax), min, cMin)
        );

        return mix(result, source, equal<int>(cMax, cMin));
    }
}
