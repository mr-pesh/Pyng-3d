#include <limits>

namespace
{
    template <bool isFloatingPoint>
    struct GLMVectorGeometryHelper;

    template <>
    struct GLMVectorGeometryHelper<true>
    {
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto AngleBetweenNormals(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::angle(vec1, vec2);
            } else {
                return glm::extensions::angle(vec1, glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto AngleBetweenVectors(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::vectorAngle(vec1, vec2);
            } else {
                return glm::extensions::vectorAngle(vec1, glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto ClampLength(const glm::vec<L, T, Q> &vector, float min, float max) noexcept
        {
            return glm::extensions::clampLength(vector, min, max);
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto Distance(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::distance(vec1, vec2);
            }
            else {
                return glm::extensions::distance(vec1, glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto DotProduct(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::dot(vec1, vec2);
            } else {
                return glm::extensions::dot(vec1, glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, typename T3, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto Faceforward(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2, const glm::vec<L, T3, Q> &nref) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::faceforward(vec1, vec2, nref);
            }
            else {
                return glm::faceforward(vec1, glm::vec<L, float_t, Q>(vec2), nref);
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto Normalize(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::normalize(vec);
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER bool InBounds(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::inBounds(vec1, vec2);
            }
            else {
                return glm::extensions::inBounds(vec1, glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER bool IsNormalized(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::isNormalized(vec, std::numeric_limits<T>::epsilon());
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto CrossProduct(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::cross(vec1, vec2);
            } else {
                return glm::cross(vec1, glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto Length(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::extensions::length(vec);
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto LengthSq(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::extensions::length2(vec);
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto LinePointDistance(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T1, Q> &vec2, const glm::vec<L, T2, Q> &vec3) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::linePointDistance(vec1, vec2, vec3);
            }
            else {
                return glm::extensions::linePointDistance(vec1, vec2, glm::vec<L, float_t, Q>(vec3));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto OrthogonalVector(const glm::vec<L, T, Q> &vector) noexcept
        {
            return glm::extensions::orthogonal(vector);
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto ReciprocalLength(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::extensions::reciprocalLength(vec);
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto Reflect(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::reflect(vec1, vec2);
            }
            else {
                return glm::reflect(vec1, glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q, typename Index>
        static GLM_FUNC_QUALIFIER auto Refract(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2, Index index) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::refract(vec1, vec2, index);
            }
            else {
                return glm::refract(vec1, glm::vec<L, float_t, Q>(vec2), index);
            }
        }
    };

    template <>
    struct GLMVectorGeometryHelper<false>
    {
        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto AngleBetweenNormals(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::angle(glm::vec<L, float_t, Q>(vec1), vec2);
            } else {
                return glm::extensions::angle(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto AngleBetweenVectors(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::vectorAngle(glm::vec<L, float_t, Q>(vec1), vec2);
            } else {
                return glm::extensions::vectorAngle(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto ClampLength(const glm::vec<L, T, Q> &vector, float min, float max) noexcept
        {
            return glm::extensions::clampLength(glm::vec<L, float_t, Q>(vector), min, max);
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto Distance(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::distance(glm::vec<L, float_t, Q>(vec1), vec2);
            }
            else {
                return glm::extensions::distance(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto DotProduct(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::dot(glm::vec<L, float_t, Q>(vec1), vec2);
            } else {
                return glm::extensions::dot(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto Normalize(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::normalize(glm::vec<L, float_t, Q>(vec));
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER bool IsNormalized(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::isNormalized(glm::vec<L, float_t, Q>(vec), std::numeric_limits<float_t>::epsilon());
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto CrossProduct(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::cross(glm::vec<L, float_t, Q>(vec1), vec2);
            } else {
                return glm::cross(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, typename T3, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto Faceforward(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2, const glm::vec<L, T3, Q> &nref) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::faceforward(glm::vec<L, float_t, Q>(vec1), vec2, nref);
            }
            else {
                return glm::faceforward(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2), nref);
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER bool InBounds(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::inBounds(glm::vec<L, float_t, Q>(vec1), vec2);
            }
            else {
                return glm::extensions::inBounds(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto Length(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::extensions::length(glm::vec<L, float_t, Q>(vec));
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto LengthSq(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::extensions::length2(glm::vec<L, float_t, Q>(vec));
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto LinePointDistance(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T1, Q> &vec2, const glm::vec<L, T2, Q> &vec3) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::extensions::linePointDistance(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2), vec3);
            }
            else {
                return glm::extensions::linePointDistance(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2), glm::vec<L, float_t, Q>(vec3));
            }
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto OrthogonalVector(const glm::vec<L, T, Q> &vector) noexcept
        {
            return glm::extensions::orthogonal(glm::vec<L, float_t, Q>(vector));
        }

        template <glm::length_t L, typename T, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto ReciprocalLength(const glm::vec<L, T, Q> &vec) noexcept
        {
            return glm::extensions::reciprocalLength(glm::vec<L, float_t, Q>(vec));
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
        static GLM_FUNC_QUALIFIER auto Reflect(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::reflect(glm::vec<L, float_t, Q>(vec1), vec2);
            }
            else {
                return glm::reflect(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2));
            }
        }

        template <glm::length_t L, typename T1, typename T2, glm::qualifier Q, typename Index>
        static GLM_FUNC_QUALIFIER auto Refract(const glm::vec<L, T1, Q> &vec1, const glm::vec<L, T2, Q> &vec2, Index index) noexcept
        {
            if constexpr (std::is_floating_point_v<T2>) {
                return glm::refract(glm::vec<L, float_t, Q>(vec1), vec2, index);
            }
            else {
                return glm::refract(glm::vec<L, float_t, Q>(vec1), glm::vec<L, float_t, Q>(vec2), index);
            }
        }
    };
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto AngleBetweenNormals(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T1>>::AngleBetweenNormals(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto AngleBetweenVectors(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T1>>::AngleBetweenVectors(vector1, vector2);
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto ClampLength(const glm::vec<L, T, Q> &vector, float min, float max) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T>>::ClampLength(vector, min, max);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto CrossProduct(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T1>>::CrossProduct(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Distance(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T1>>::Distance(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto DotProduct(const glm::vec<L, T1, Q> &vector1, const glm::vec<L, T2, Q> &vector2) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T1>>::DotProduct(vector1, vector2);
}

template <glm::length_t L, typename T1, typename T2, typename T3, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Faceforward(const glm::vec<L, T1, Q> &normal, const glm::vec<L, T2, Q> &vector, const glm::vec<L, T3, Q> &nref) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T1>>::Faceforward(normal, vector, nref);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER bool InBounds(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &bounds) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T1>>::InBounds(vector, bounds);
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER bool IsNormalized(const glm::vec<L, T, Q> &vector) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T>>::IsNormalized(vector);
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Length(const glm::vec<L, T, Q> &vector) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T>>::Length(vector);
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto LengthSq(const glm::vec<L, T, Q> &vector) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T>>::LengthSq(vector);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto LinePointDistance(const glm::vec<L, T1, Q> &linePoint1, const glm::vec<L, T1, Q> &linePoint2, const glm::vec<L, T2, Q> &point) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T1>>::LinePointDistance(linePoint1, linePoint2, point);
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Normalize(const glm::vec<L, T, Q> &vector) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T>>::Normalize(vector);
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto OrthogonalVector(const glm::vec<L, T, Q> &vector) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T>>::OrthogonalVector(vector);
}

template <glm::length_t L, typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto ReciprocalLength(const glm::vec<L, T, Q> &vector) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T>>::ReciprocalLength(vector);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Reflect(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &normal) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T1>>::Reflect(vector, normal);
}

template <glm::length_t L, typename T1, typename T2, glm::qualifier Q>
GLM_FUNC_QUALIFIER auto Refract(const glm::vec<L, T1, Q> &vector, const glm::vec<L, T2, Q> &normal, std::common_type_t<T1, T2, float_t> refractionIndex) noexcept
{
    return GLMVectorGeometryHelper<std::is_floating_point_v<T1>>::Refract(vector, normal, refractionIndex);
}
