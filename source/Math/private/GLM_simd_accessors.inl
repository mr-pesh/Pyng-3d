/**
 * Return the X component in FPU register.
 */
GLM_FUNC_QUALIFIER float glm_vec4_getX(glm_vec4 vec)
{
    return _mm_cvtss_f32(vec);
}

/**
 * Return the Y component in FPU register.
 */
GLM_FUNC_QUALIFIER float glm_vec4_getY(glm_vec4 vec)
{
    return _mm_cvtss_f32(_mm_shuffle_ps(vec, vec, _MM_SHUFFLE(1,1,1,1)));
}

/**
 * Return the Z component in FPU register.
 */
GLM_FUNC_QUALIFIER float glm_vec4_getZ(glm_vec4 vec)
{
    return _mm_cvtss_f32(_mm_shuffle_ps(vec, vec, _MM_SHUFFLE(2,2,2,2)));
}

/**
 * Return the W component in FPU register.
 */
GLM_FUNC_QUALIFIER float glm_vec4_getW(glm_vec4 vec)
{
    return _mm_cvtss_f32(_mm_shuffle_ps(vec, vec, _MM_SHUFFLE(3,3,3,3)));
}

/**
 * Loads an ivec2 into a glm_vec4.
 */
template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<2, int32_t, Q> &vec) noexcept
{
    return _mm_cvtepi32_ps(_mm_castps_si128(
                               _mm_unpacklo_ps(
                                   _mm_load_ss((const float*)(&vec.x)),
                                   _mm_load_ss((const float*)(&vec.y))
                               )));
}

/**
 * Loads an ivec3 into a glm_vec4.
 */
template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<3, int32_t, Q> &vec) noexcept
{
    return _mm_cvtepi32_ps(
                _mm_castps_si128(
                    _mm_movelh_ps(
                        _mm_unpacklo_ps(_mm_load_ss((const float*)(&vec.x)),
                                        _mm_load_ss((const float*)(&vec.y))),
                                        _mm_load_ss((const float*)(&vec.z)))
                    ));
}

/**
 * Loads an ivec4 into a glm_vec4.
 */
template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<4, int32_t, Q> &vec) noexcept
{
    return _mm_cvtepi32_ps(_mm_loadu_si128((const glm_ivec4*)(&vec)));
}

/**
 * Loads vec2 into a glm_vec4.
 */
template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<2, float_t, Q> &vec) noexcept
{
    return _mm_unpacklo_ps(_mm_load_ss(&vec.x), _mm_load_ss(&vec.y));
}

/**
 * Loads vec3 into a glm_vec4.
 */
template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<3, float_t, Q> &vec) noexcept
{
    return _mm_movelh_ps(
                _mm_unpacklo_ps(
                    _mm_load_ss(&vec.x), _mm_load_ss(&vec.y)), _mm_load_ss(&vec.z));
}

/**
 * Loads vec4 into a glm_vec4.
 */
template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<4, float_t, Q> &vec) noexcept
{
    return _mm_loadu_ps(&vec.x);
}

/**
 * Loads an uvec2 into a glm_vec4.
 */
template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<2, uint32_t, Q> &vec) noexcept
{
    glm_vec4 val = _mm_unpacklo_ps(_mm_load_ss((const float*)(&vec.x)), _mm_load_ss((const float*)(&vec.y)));
    glm_vec4 vMask = _mm_and_ps(val, SSE2_NEG_ZERO);
    glm_vec4 result = _mm_cvtepi32_ps(_mm_castps_si128(_mm_xor_ps(val, vMask)));
    glm_ivec4 iMask = _mm_srai_epi32(_mm_castps_si128(vMask),31);

    return _mm_add_ps(result, _mm_and_ps(_mm_castsi128_ps(iMask), SSE2_FIX_UINT));
}

/**
 * Loads an uvec3 into a glm_vec4.
 */
template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<3, uint32_t, Q> &vec) noexcept
{
    glm_vec4 val =
            _mm_movelh_ps(
                _mm_unpacklo_ps(_mm_load_ss((const float*)(&vec.x)),
                                _mm_load_ss((const float*)(&vec.y))),
                                _mm_load_ss((const float*)(&vec.z)));

    glm_vec4 vMask = _mm_and_ps(val, SSE2_NEG_ZERO);
    glm_vec4 result = _mm_xor_ps(val, vMask);
    glm_ivec4 iMask = _mm_srai_epi32(_mm_castps_si128(vMask),31);

    return _mm_add_ps(_mm_cvtepi32_ps(_mm_castps_si128(result)), _mm_and_ps(_mm_castsi128_ps(iMask), SSE2_FIX_UINT));
}

/**
 * Loads an uvec4 into a glm_vec4.
 */
template <glm::qualifier Q>
GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_load(const glm::vec<4, uint32_t, Q> &vec) noexcept
{
    glm_ivec4 val = _mm_loadu_si128((const glm_ivec4*)(&vec));
    glm_vec4 vMask = _mm_and_ps(_mm_castsi128_ps(val), SSE2_NEG_ZERO);
    glm_vec4 result = _mm_xor_ps(_mm_castsi128_ps(val), vMask);
    glm_ivec4 iMask = _mm_srai_epi32(_mm_castps_si128(vMask), 31);

    return _mm_add_ps(_mm_cvtepi32_ps(_mm_castps_si128(result)), _mm_and_ps(_mm_castsi128_ps(iMask), SSE2_FIX_UINT));
}
