#pragma once

#include <glm/detail/setup.hpp>

#if (GLM_ARCH & GLM_ARCH_AVX_BIT)
#define _MM_PERMUTE_PS(v,c) _mm_permute_ps(v,c)
#else
#define _MM_PERMUTE_PS(v,c) _mm_shuffle_ps(v,v,c)
#endif

/**
 * Return the X component of \ref glm_vec4.
 */
template <typename T = float_t>
GLM_FUNC_QUALIFIER T glm_vec4_getX(glm_vec4 vec) noexcept;

/**
 * Return the Y component of \ref glm_vec4.
 */
template <typename T = float_t>
GLM_FUNC_QUALIFIER T glm_vec4_getY(glm_vec4 vec) noexcept;

/**
 * Return the Z component of \ref glm_vec4.
 */
template <typename T = float_t>
GLM_FUNC_QUALIFIER T glm_vec4_getZ(glm_vec4 vec) noexcept;

/**
 * Return the W component of \ref glm_vec4.
 */
template <typename T = float_t>
GLM_FUNC_QUALIFIER T glm_vec4_getW(glm_vec4 vec) noexcept;

/**
 * Retrieve the X component of \ref glm_vec4 and stores it's value in a 32-bit **T** referenced by a pointer.
 */
template <typename T = float_t>
GLM_FUNC_QUALIFIER void glm_vec4_getX(T *x, glm_vec4 vec) noexcept;

/**
 * Retrieve the Y component of \ref glm_vec4 and stores it's value in a 32-bit **T** referenced by a pointer.
 */
template <typename T = float_t>
GLM_FUNC_QUALIFIER void glm_vec4_getY(T *y, glm_vec4 vec) noexcept;

/**
 * Retrieve the Z component of \ref glm_vec4 and stores it's value in a 32-bit **T** referenced by a pointer.
 */
template <typename T = float_t>
GLM_FUNC_QUALIFIER void glm_vec4_getZ(T *z, glm_vec4 vec) noexcept;

/**
 * Retrieve the W component of \ref glm_vec4 and stores it's value in a 32-bit **T** referenced by a pointer.
 */
template <typename T = float_t>
GLM_FUNC_QUALIFIER void glm_vec4_getW(T *w, glm_vec4 vec) noexcept;


#include "GLM_simd_accessors.inl"
