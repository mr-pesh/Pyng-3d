#pragma once

#include <glm/gtx/closest_point.hpp>

#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/vector_query.hpp>

#include <glm/gtx/vec_swizzle.hpp>

#if (GLM_ARCH & GLM_ARCH_SSE2_BIT)

#include <glm/simd/geometric.h>

namespace glm
{
    /**
     * \brief Clamps the length of a vector to a given range.
     * \param source A vector to clamp.
     * \param min Minimum clamp length.
     * \param max Maximum clamp length.
     * \return A vector with length clamped to the specified minimum and maximum.
     */
    template <glm::length_t>
    GLM_FUNC_QUALIFIER glm_vec4 clampLength(glm_vec4 source, float min, float max) noexcept;
    /**
     * \brief Clamps the length of a vector to a given range.
     * \param source A vector to clamp.
     * \param min Vector with all components equal to the minimum clamp length. The components must be greater-than-or-equal to zero.
     * \param max Vector with all components equal to the maximum clamp length. The components must be greater-than-or-equal to zero.
     * \return A vector with length clamped to the specified minimum and maximum.
     */
    template <glm::length_t>
    GLM_FUNC_QUALIFIER glm_vec4 clampLength(glm_vec4 source, glm_vec4 min, glm_vec4 max) noexcept;

    /**
     * \brief Computes the dot product between vectors.
     * \param vec1 N-dimensional vector packed in <a href="https://docs.microsoft.com/en-us/cpp/cpp/m128">__m128</a> struct
     * \param vec2 N-dimensional vector packed in <a href="https://docs.microsoft.com/en-us/cpp/cpp/m128">__m128</a> struct
     * \return Returns a vector. The dot product between vec1 and vec2 is replicated into each component.
     */
    template <glm::length_t>
    GLM_FUNC_QUALIFIER glm_vec4 dot(glm_vec4 vec1, glm_vec4 vec2) noexcept;

    /**
     * \brief Performs a per-component test for greater-than-or-equal between two vectors.
     * \param vec1 First vector to compare.
     * \param vec2 Second vector to compare.
     * \return Returns a vector containing the results of each component test.
     */
    template <glm::length_t>
    GLM_FUNC_QUALIFIER bool greaterThanEqual(glm_vec4 vec1, glm_vec4 vec2) noexcept;

    /**
     * \brief Performs a per-component test for equality of two vectors.
     * \param vec1 First vector to compare.
     * \param vec2 Second vector to compare.
     * \return Returns a vector containing the results of each component test.
     */
    template <typename T = float_t>
    GLM_FUNC_QUALIFIER glm_vec4 equal(glm_vec4 vec1, glm_vec4 vec2) noexcept;

    /**
     * \brief Computes the per-component reciprocal square root of a vector.
     * \param vec Vector whose reciprocal square root is computed.
     * \return Returns a vector. Each component is the reciprocal square-root of the corresponding component of vec.
     */
    GLM_FUNC_QUALIFIER glm_vec4 inversesqrt(glm_vec4 vec) noexcept;

    /**
     * \brief Computes the square of the length of a vector.
     * \param vec N-dimensional vector packed in <a href="https://docs.microsoft.com/en-us/cpp/cpp/m128">__m128</a>
     * \return Returns a vector. The square of the length of vec is replicated into each component.
     */
    template <glm::length_t L>
    GLM_FUNC_QUALIFIER glm_vec4 length2(glm_vec4 vec) noexcept;

    /**
     * \brief Performs a per-component selection between two input vectors and returns the resulting vector.
     * \param left First vector to compare.
     * \param right Second vector to compare.
     * \param control Vector mask used to select a vector component from either left or right. If a component of control is zero, the returned vector's corresponding component will be the first vector's component. If a component of control is 0xFF, the returned vector's corresponding component will be the second vector's component
     * \return The result of the per-component selection
     */
    GLM_FUNC_QUALIFIER glm_vec4 mix(glm_vec4 left, glm_vec4 right, glm_vec4 control) noexcept;
}
#include "GLM_simd_accessors.inl"
#include "GLM_simd_constants.inl"
#include "GLM_simd_extension.inl"

#else

namespace glm
{
    /**
     * \brief Clamps the length of a vector to a given range.
     * \param source A vector to clamp.
     * \param min Minimum clamp length.
     * \param max Maximum clamp length.
     * \return A vector with length clamped to the specified minimum and maximum.
     */
    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<L, T, Q> clampLength(const vec<L, T, Q> &source, float &min, float &max) noexcept;

    /**
     * \brief Clamps the length of a vector to a given range.
     * \param source A vector to clamp.
     * \param min Vector with all components equal to the minimum clamp length. The components must be greater-than-or-equal to zero.
     * \param max Vector with all components equal to the maximum clamp length. The components must be greater-than-or-equal to zero.
     * \return A vector with length clamped to the specified minimum and maximum.
     */
    template <length_t L, typename T, qualifier Q>
    GLM_FUNC_QUALIFIER vec<L, T, Q> clampLength(const vec<L, T, Q> &source, const vec<L, T, Q> &min, const vec<L, T, Q> &max) noexcept;

    /**
     * \brief Computes a vector perpendicular to a given vector.
     * \param source N-dimensional vector packed in <a href="https://glm.g-truc.net/0.9.2/api/a00236.html#gac422c7058a7c9963b55ad70764c62752">glm::vec</a> struct
     * \return Returns a vector orthogonal to source.
     */
    template <length_t L, typename T, qualifier Q>
    static GLM_FUNC_QUALIFIER glm::vec<L, T, Q> orthogonal(const glm::vec<L, T, Q> &source) noexcept;
}
#include "GLM_pure_extension.inl"

#endif // !GLM_ARCH_SSE2
