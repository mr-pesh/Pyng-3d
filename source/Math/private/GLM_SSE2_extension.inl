namespace glm
{
    GLM_FUNC_QUALIFIER glm_vec4 acos(glm_vec4 vec) noexcept
    {
        glm_vec4 xx = _mm_max_ps(vec, _mm_sub_ps(SSE2_ZERO_VEC, vec));
        glm_vec4 nn = _mm_cmpge_ps(vec, SSE2_ZERO_VEC);

        glm_vec4 sqrt =
                _mm_sqrt_ps(
                    _mm_max_ps(SSE2_ZERO_VEC, _mm_sub_ps(SSE2_POS_ONE, xx)));

        const glm_vec4 arcc0 = _mm_set_ps(-0.0012624911f, 0.0066700901f, -0.0170881256f, 0.0308918810f);

        glm_vec4 mul0 = _mm_mul_ps(_MM_PERMUTE_PS(arcc0, _MM_SHUFFLE(3, 3, 3, 3)), xx);
        mul0 = _mm_mul_ps(_mm_add_ps(mul0, _MM_PERMUTE_PS(arcc0, _MM_SHUFFLE(2, 2, 2, 2))), xx);
        mul0 = _mm_mul_ps(_mm_add_ps(mul0, _MM_PERMUTE_PS(arcc0, _MM_SHUFFLE(1, 1, 1, 1))), xx);
        mul0 = _mm_mul_ps(_mm_add_ps(mul0, _MM_PERMUTE_PS(arcc0, _MM_SHUFFLE(0, 0, 0, 0))), xx);

        const glm_vec4 arcc1 = _mm_set_ps(-0.0501743046f, 0.0889789874f, -0.2145988016f, 1.5707963050f);

        mul0 = _mm_mul_ps(_mm_add_ps(mul0, _MM_PERMUTE_PS(arcc1, _MM_SHUFFLE(3, 3, 3, 3))), xx);
        mul0 = _mm_mul_ps(_mm_add_ps(mul0, _MM_PERMUTE_PS(arcc1, _MM_SHUFFLE(2, 2, 2, 2))), xx);
        mul0 = _mm_mul_ps(_mm_add_ps(mul0, _MM_PERMUTE_PS(arcc1, _MM_SHUFFLE(1, 1, 1, 1))), xx);
        mul0 = _mm_mul_ps(_mm_add_ps(mul0, _MM_PERMUTE_PS(arcc1, _MM_SHUFFLE(0, 0, 0, 0))), sqrt);

        return _mm_or_ps(_mm_and_ps(nn, mul0), _mm_andnot_ps(nn, _mm_sub_ps(SSE2_PI_VEC, mul0)));
    }

    template <length_t L>
    GLM_FUNC_QUALIFIER glm_vec4 angle(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        return acos(glm_vec4_clamp(dot<L>(vec1, vec2), SSE2_NEG_ONE, SSE2_POS_ONE));
    }

    template <>
    GLM_FUNC_QUALIFIER glm_vec4 dot<2>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        glm_vec4 mul0 = _mm_mul_ps(vec1, vec2);
        glm_vec4 swp0 = _MM_PERMUTE_PS(mul0, _MM_SHUFFLE(1, 1, 1, 1));
        return _MM_PERMUTE_PS(_mm_add_ss(mul0, swp0), _MM_SHUFFLE(0, 0, 0, 0));
    }

    template <>
    GLM_FUNC_QUALIFIER glm_vec4 dot<3>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        glm_vec4 mul0 = _mm_mul_ps(vec1, vec2);
        glm_vec4 swp0 = _MM_PERMUTE_PS(mul0, _MM_SHUFFLE(2, 1, 2, 1));
        mul0 = _mm_add_ss(mul0, swp0);
        swp0 = _MM_PERMUTE_PS(swp0, _MM_SHUFFLE(1, 1, 1, 1));
        return _MM_PERMUTE_PS(_mm_add_ss(mul0, swp0), _MM_SHUFFLE(0, 0, 0, 0));
    }

    template <>
    GLM_FUNC_QUALIFIER glm_vec4 dot<4>(glm_vec4 vec1, glm_vec4 vec2) noexcept
    {
        glm_vec4 mul0 = _mm_mul_ps(vec1, vec2);
        glm_vec4 add0 = _mm_add_ps(_mm_shuffle_ps(vec2, mul0, _MM_SHUFFLE(1,0,0,0)), mul0);
        return _MM_PERMUTE_PS(
                    _mm_add_ps(
                        _mm_shuffle_ps(mul0, add0, _MM_SHUFFLE(0,3,0,0)), add0), _MM_SHUFFLE(2,2,2,2));
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
        return dot<L>(vec, vec);
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
