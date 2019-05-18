template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<2, int32_t, Q> &vec) noexcept
{
    return _mm_cvtepi32_ps(_mm_castps_si128(
                               _mm_unpacklo_ps(
                                   _mm_load_ss(reinterpret_cast<const float*>(&vec.x)),
                                   _mm_load_ss(reinterpret_cast<const float*>(&vec.y))
                               )));
}

template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<3, int32_t, Q> &vec) noexcept
{
    return _mm_cvtepi32_ps(
                _mm_castps_si128(
                    _mm_movelh_ps(
                        _mm_unpacklo_ps(_mm_load_ss(reinterpret_cast<const float*>(&vec.x)),
                                        _mm_load_ss(reinterpret_cast<const float*>(&vec.y))),
                                        _mm_load_ss(reinterpret_cast<const float*>(&vec.z)))
                    ));
}

template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<4, int32_t, Q> &vec) noexcept
{
    return _mm_cvtepi32_ps(_mm_loadu_si128(reinterpret_cast<const glm_ivec4*>(&vec)));
}

template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<2, float_t, Q> &vec) noexcept
{
    return _mm_unpacklo_ps(_mm_load_ss(&vec.x), _mm_load_ss(&vec.y));
}

template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<3, float_t, Q> &vec) noexcept
{
    return _mm_movelh_ps(
                _mm_unpacklo_ps(
                    _mm_load_ss(&vec.x), _mm_load_ss(&vec.y)), _mm_load_ss(&vec.z));
}

template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<4, float_t, Q> &vec) noexcept
{
    return _mm_loadu_ps(&vec.x);
}

template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<2, uint32_t, Q> &vec) noexcept
{
    glm_vec4 val =
            _mm_unpacklo_ps(
                _mm_load_ss(reinterpret_cast<const float*>(&vec.x)),
                _mm_load_ss(reinterpret_cast<const float*>(&vec.y)));

    glm_vec4 vMask = _mm_and_ps(val, SSE2_NEG_ZERO);
    glm_vec4 result = _mm_cvtepi32_ps(_mm_castps_si128(_mm_xor_ps(val, vMask)));
    glm_ivec4 iMask = _mm_srai_epi32(_mm_castps_si128(vMask), 31);

    return _mm_add_ps(result, _mm_and_ps(_mm_castsi128_ps(iMask), SSE2_FIX_UINT));
}

template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<3, uint32_t, Q> &vec) noexcept
{
    glm_vec4 val =
            _mm_movelh_ps(
                _mm_unpacklo_ps(_mm_load_ss(reinterpret_cast<const float*>(&vec.x)),
                                _mm_load_ss(reinterpret_cast<const float*>(&vec.y))),
                                _mm_load_ss(reinterpret_cast<const float*>(&vec.z)));

    glm_vec4 vMask = _mm_and_ps(val, SSE2_NEG_ZERO);
    glm_vec4 result = _mm_xor_ps(val, vMask);
    glm_ivec4 iMask = _mm_srai_epi32(_mm_castps_si128(vMask), 31);

    return _mm_add_ps(_mm_cvtepi32_ps(_mm_castps_si128(result)), _mm_and_ps(_mm_castsi128_ps(iMask), SSE2_FIX_UINT));
}

template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<4, uint32_t, Q> &vec) noexcept
{
    glm_ivec4 val = _mm_loadu_si128(reinterpret_cast<const glm_ivec4*>(&vec));
    glm_vec4 vMask = _mm_and_ps(_mm_castsi128_ps(val), SSE2_NEG_ZERO);
    glm_vec4 result = _mm_xor_ps(_mm_castsi128_ps(val), vMask);
    glm_ivec4 iMask = _mm_srai_epi32(_mm_castps_si128(vMask), 31);

    return _mm_add_ps(_mm_cvtepi32_ps(_mm_castps_si128(result)), _mm_and_ps(_mm_castsi128_ps(iMask), SSE2_FIX_UINT));
}

namespace glm
{
    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER glm_vec4 angle(const vec<L, T, Q> &v1, const vec<L, T, Q> &v2) noexcept
    {
        return angle<L>(glm_vec4_load(v1), glm_vec4_load(v2));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER glm_vec4 clampLength(const vec<L, T, Q> &v, float_t min, float_t max) noexcept
    {
        return clampLength<L>(glm_vec4_load(v), min, max);
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER glm_vec4 clampLength(const vec<L, T, Q> &v1, const vec<L, T, Q> &v2, const vec<L, T, Q> &v3) noexcept
    {
        return clampLength<L>(glm_vec4_load(v1), glm_vec4_load(v2), glm_vec4_load(v3));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER glm_vec4 dot(const vec<L, T, Q> &v1, const vec<L, T, Q> &v2) noexcept
    {
        return dot<L>(glm_vec4_load(v1), glm_vec4_load(v2));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER bool greaterThanEqual(const vec<L, T, Q> &v1, const vec<L, T, Q> &v2) noexcept
    {
        return greaterThanEqual<L>(glm_vec4_load(v1), glm_vec4_load(v2));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER glm_vec4 equal(const vec<L, T, Q> &v1, const vec<L, T, Q> &v2) noexcept
    {
        return equal<T>(glm_vec4_load(v1), glm_vec4_load(v2));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER glm_vec4 inversesqrt(const vec<L, T, Q> &v) noexcept
    {
        return inversesqrt(glm_vec4_load(v));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER glm_vec4 length2(const vec<L, T, Q> &v) noexcept
    {
        return length2<L>(glm_vec4_load(v));
    }

    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER glm_vec4 mix(const vec<L, T, Q> &v1, const vec<L, T, Q> &v2, const vec<L, T, Q> &v3) noexcept
    {
        return mix(glm_vec4_load(v1), glm_vec4_load(v2), glm_vec4_load(v3));
    }
}
