template <typename T>
GLM_FUNC_QUALIFIER T glm_vec4_getX(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return static_cast<T>(vgetq_lane_u32(vec, 0));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return static_cast<T>(_mm_cvtsi128_si32(_mm_castps_si128(vec)));
#endif
}

template <>
GLM_FUNC_QUALIFIER float glm_vec4_getX<float>(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_f32(vec, 0);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return _mm_cvtss_f32(vec);
#endif
}

template <typename T>
GLM_FUNC_QUALIFIER T glm_vec4_getY(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return static_cast<T>(vgetq_lane_u32(vec, 1));
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    return static_cast<T>(_mm_extract_epi32(_mm_castps_si128(vec), 1));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return static_cast<T>(_mm_cvtsi128_si32(_mm_shuffle_epi32(_mm_castps_si128(vec), _MM_SHUFFLE(1,1,1,1))));
#endif
}

template <>
GLM_FUNC_QUALIFIER float glm_vec4_getY<float>(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_f32(vec, 1);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return _mm_cvtss_f32(_MM_PERMUTE_PS(vec, _MM_SHUFFLE(1,1,1,1)));
#endif
}

template <typename T>
GLM_FUNC_QUALIFIER T glm_vec4_getZ(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return static_cast<T>(vgetq_lane_u32(vec, 2));
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    return static_cast<T>(_mm_extract_epi32(_mm_castps_si128(vec), 2));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return static_cast<T>(_mm_cvtsi128_si32(_mm_shuffle_epi32(_mm_castps_si128(vec), _MM_SHUFFLE(2,2,2,2))));
#endif
}

template <>
GLM_FUNC_QUALIFIER float glm_vec4_getZ<float>(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_f32(vec, 2);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return _mm_cvtss_f32(_MM_PERMUTE_PS(vec, _MM_SHUFFLE(2,2,2,2)));
#endif
}

template <typename T>
GLM_FUNC_QUALIFIER T glm_vec4_getW(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return static_cast<T>(vgetq_lane_u32(vec, 3));
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    return static_cast<T>(_mm_extract_epi32(_mm_castps_si128(vec), 3));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return static_cast<T>(_mm_cvtsi128_si32(_mm_shuffle_epi32(_mm_castps_si128(vec), _MM_SHUFFLE(3,3,3,3))));
#endif
}

template <>
GLM_FUNC_QUALIFIER float glm_vec4_getW<float>(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_f32(vec, 3);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return _mm_cvtss_f32(_MM_PERMUTE_PS(vec, _MM_SHUFFLE(3,3,3,3)));
#endif
}

template <typename T>
GLM_FUNC_QUALIFIER void glm_vec4_getX(T *x, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_u32(x, *reinterpret_cast<const uint32x4_t*>(&vec), 0);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(reinterpret_cast<float*>(x), vec);
#endif
}

template <>
GLM_FUNC_QUALIFIER void glm_vec4_getX<float>(float *x, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_f32(x, vec, 0);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(x, vec);
#endif
}

template <typename T>
GLM_FUNC_QUALIFIER void glm_vec4_getY(T *y, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_u32(y, *reinterpret_cast<const uint32x4_t*>(&vec), 1);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    *y = static_cast<T>(_mm_extract_epi32(_mm_castps_si128(vec), 1));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(reinterpret_cast<float*>(y), _MM_PERMUTE_PS(vec, _MM_SHUFFLE(1,1,1,1)));
#endif
}

template <>
GLM_FUNC_QUALIFIER void glm_vec4_getY<float>(float *y, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_f32(y, vec, 1);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(y, _MM_PERMUTE_PS(vec, _MM_SHUFFLE(1,1,1,1)));
#elif (GLM_ARCH & GLM_ARCH_SSE41_BIT)
    *(reinterpret_cast<int*>(y)) = _mm_extract_ps(vec, 1);
#endif
}

template <typename T>
GLM_FUNC_QUALIFIER void glm_vec4_getZ(T *z, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_u32(z, *reinterpret_cast<const uint32x4_t*>(&vec), 2);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    *z = static_cast<T>(_mm_extract_epi32(_mm_castps_si128(vec), 2));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(reinterpret_cast<float*>(z), _MM_PERMUTE_PS(vec, _MM_SHUFFLE(2,2,2,2)));
#endif
}

template <>
GLM_FUNC_QUALIFIER void glm_vec4_getZ<float>(float *z, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_f32(z, vec, 2);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(z, _MM_PERMUTE_PS(vec, _MM_SHUFFLE(2,2,2,2)));
#elif (GLM_ARCH & GLM_ARCH_SSE41_BIT)
    *(reinterpret_cast<int*>(z)) = _mm_extract_ps(vec, 2);
#endif
}

template <typename T>
GLM_FUNC_QUALIFIER void glm_vec4_getW(T *w, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_u32(w, *reinterpret_cast<const uint32x4_t*>(&vec), 3);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    *w = static_cast<T>(_mm_extract_epi32(_mm_castps_si128(vec), 3));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(reinterpret_cast<float*>(w), _MM_PERMUTE_PS(vec, _MM_SHUFFLE(3,3,3,3)));
#endif
}

template <>
GLM_FUNC_QUALIFIER void glm_vec4_getW<float>(float *w, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_f32(w, vec, 3);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(w, _MM_PERMUTE_PS(vec, _MM_SHUFFLE(3,3,3,3)));
#elif (GLM_ARCH & GLM_ARCH_SSE41_BIT)
    *(reinterpret_cast<int*>(w)) = _mm_extract_ps(vec, 3);
#endif
}
