#pragma once

#include <glm/detail/setup.hpp>

#if (GLM_ARCH & GLM_ARCH_AVX_BIT)
#define _MM_PERMUTE_PS(v,c) _mm_permute_ps(v,c)
#else
#define _MM_PERMUTE_PS(v,c) _mm_shuffle_ps(v,v,c)
#endif

/**
 * Return the X component of glm_vec4.
 */
GLM_FUNC_QUALIFIER float glm_vec4_getX(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_f32(vec, 0);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return _mm_cvtss_f32(vec);
#endif
}

/**
 * Return the Y component of glm_vec4.
 */
GLM_FUNC_QUALIFIER float glm_vec4_getY(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_f32(vec, 1);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return _mm_cvtss_f32(_MM_PERMUTE_PS(vec, _MM_SHUFFLE(1,1,1,1)));
#endif
}

/**
 * Return the Z component of glm_vec4.
 */
GLM_FUNC_QUALIFIER float glm_vec4_getZ(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_f32(vec, 2);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return _mm_cvtss_f32(_MM_PERMUTE_PS(vec, _MM_SHUFFLE(2,2,2,2)));
#endif
}

/**
 * Return the W component of glm_vec4.
 */
GLM_FUNC_QUALIFIER float glm_vec4_getW(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_f32(vec, 3);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return _mm_cvtss_f32(_MM_PERMUTE_PS(vec, _MM_SHUFFLE(3,3,3,3)));
#endif
}

/**
 * Retrieve the X component of glm_vec4 and stores it's value in a float referred by a pointer.
 */
GLM_FUNC_QUALIFIER void glm_vec4_getX(float *x, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_f32(x, vec, 0);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(x, vec);
#endif
}

/**
 * Retrieve the Y component of glm_vec4 and stores it's value in a float referred by a pointer.
 */
GLM_FUNC_QUALIFIER void glm_vec4_getY(float *y, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_f32(y, vec, 1);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    *((int*)y) = _mm_extract_ps(vec, 1);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(y, _MM_PERMUTE_PS(vec, _MM_SHUFFLE(1,1,1,1)));
#endif
}

/**
 * Retrieve the Z component of glm_vec4 and stores it's value in a float referred by a pointer.
 */
GLM_FUNC_QUALIFIER void glm_vec4_getZ(float *z, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_f32(z, vec, 2);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    *((int*)z) = _mm_extract_ps(vec, 2);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(z, _MM_PERMUTE_PS(vec, _MM_SHUFFLE(2,2,2,2)));
#endif
}

/**
 * Retrieve the W component of glm_vec4 and stores it's value in a float referred by a pointer.
 */
GLM_FUNC_QUALIFIER void glm_vec4_getW(float *w, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_f32(w, vec, 3);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    *((int*)w) = _mm_extract_ps(vec, 3);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss(w, _MM_PERMUTE_PS(vec, _MM_SHUFFLE(3,3,3,3)));
#endif
}

/**
 * Return the X component of glm_vec4.
 */
GLM_FUNC_QUALIFIER uint32_t glm_vec4_getIntX(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_u32(vec, 0);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return static_cast<uint32_t>(_mm_cvtsi128_si32(_mm_castps_si128(vec)));
#endif
}

/**
 * Return the Y component of glm_vec4.
 */
GLM_FUNC_QUALIFIER uint32_t glm_vec4_getIntY(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_u32(vec, 1);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    return static_cast<uint32_t>(_mm_extract_epi32(_mm_castps_si128(vec), 1));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return static_cast<uint32_t>(_mm_cvtsi128_si32(_mm_shuffle_epi32(_mm_castps_si128(vec), _MM_SHUFFLE(1,1,1,1))));
#endif
}

/**
 * Return the Z component of glm_vec4.
 */
GLM_FUNC_QUALIFIER uint32_t glm_vec4_getIntZ(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_u32(vec, 2);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    return static_cast<uint32_t>(_mm_extract_epi32(_mm_castps_si128(vec), 2));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return static_cast<uint32_t>(_mm_cvtsi128_si32(_mm_shuffle_epi32(_mm_castps_si128(vec), _MM_SHUFFLE(2,2,2,2))));
#endif
}

/**
 * Return the W component of glm_vec4.
 */
GLM_FUNC_QUALIFIER uint32_t glm_vec4_getIntW(glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    return vgetq_lane_u32(vec, 3);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    return static_cast<uint32_t>(_mm_extract_epi32(_mm_castps_si128(vec), 3));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    return static_cast<uint32_t>(_mm_cvtsi128_si32(_mm_shuffle_epi32(_mm_castps_si128(vec), _MM_SHUFFLE(3,3,3,3))));
#endif
}

/**
 * Retrieve the X component of glm_vec4 and stores it's value in uint32_t referred by a pointer.
 */
GLM_FUNC_QUALIFIER void glm_vec4_getIntX(uint32_t *x, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_u32(x, *reinterpret_cast<const uint32x4_t*>(&vec), 0);
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss((float*)x, vec);
#endif
}

/**
 * Retrieve the Y component of glm_vec4 and stores it's value in uint32_t referred by a pointer.
 */
GLM_FUNC_QUALIFIER void glm_vec4_getIntY(uint32_t *y, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_u32(y, *reinterpret_cast<const uint32x4_t*>(&vec), 1);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    *y = static_cast<uint32_t>(_mm_extract_epi32(_mm_castps_si128(vec), 1));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss((float*)y, _MM_PERMUTE_PS(vec, _MM_SHUFFLE(1,1,1,1)));
#endif
}

/**
 * Retrieve the Z component of glm_vec4 and stores it's value in uint32_t referred by a pointer.
 */
GLM_FUNC_QUALIFIER void glm_vec4_getIntZ(uint32_t *z, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_u32(z, *reinterpret_cast<const uint32x4_t*>(&vec), 2);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    *z = static_cast<uint32_t>(_mm_extract_epi32(_mm_castps_si128(vec), 2));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss((float*)z, _MM_PERMUTE_PS(vec, _MM_SHUFFLE(2,2,2,2)));
#endif
}

/**
 * Retrieve the W component of glm_vec4 and stores it's value in uint32_t referred by a pointer.
 */
GLM_FUNC_QUALIFIER void glm_vec4_getIntW(uint32_t *w, glm_vec4 vec) noexcept
{
#if (GLM_ARCH & GLM_ARCH_NEON_BIT)
    vst1q_lane_u32(w, *reinterpret_cast<const uint32x4_t*>(&vec), 3);
#elif (GLM_ARCH & GLM_ARCH_AVX_BIT)
    *w = static_cast<uint32_t>(_mm_extract_epi32(_mm_castps_si128(vec), 3));
#elif (GLM_ARCH & GLM_ARCH_SSE2_BIT)
    _mm_store_ss((float*)w, _MM_PERMUTE_PS(vec, _MM_SHUFFLE(3,3,3,3)));
#endif
}
