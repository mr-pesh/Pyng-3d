#include <glm/gtx/closest_point.hpp>

#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/vector_query.hpp>

#include <glm/gtx/vec_swizzle.hpp>

template <glm::length_t>
struct OrthogonalImpl;

template <>
struct OrthogonalImpl<2>
{
    template <typename T, glm::qualifier Q>
    static GLM_FUNC_QUALIFIER glm::vec<2, T, Q> Orthogonal(const glm::vec<2, T, Q> &source) noexcept
    {
        return glm::vec<2, T, Q>(-source.y, source.x);
    }
};

template <>
struct OrthogonalImpl<3>
{
    template <typename T, glm::qualifier Q>
    static GLM_FUNC_QUALIFIER glm::vec<3, T, Q> Orthogonal(const glm::vec<3, T, Q> &source) noexcept
    {
        glm::vec<3, T, Q> zero(0);

        auto ZZZ = glm::zzz(source);
        auto YZY = glm::yzy(source);
        auto nSource = -source;

        auto Is_nZZZ = glm::lessThan(ZZZ, zero);
        auto Is_nYZY = glm::lessThan(YZY, zero);

        auto S = YZY + ZZZ;
        auto D = YZY - ZZZ;

        auto sMask = glm::equal(Is_nZZZ, Is_nYZY);

        glm::vec<3, T, Q> R0(S.x, nSource.x, nSource.x);
        glm::vec<3, T, Q> R1(D.x, source.x, source.x);

        return glm::mix(R1, R0, sMask);
    }
};

template <>
struct OrthogonalImpl<4>
{
    template <typename T, glm::qualifier Q>
    static inline glm::vec<4, T, Q> Orthogonal(const glm::vec<4, T, Q> &source) noexcept
    {
        return glm::vec<4, T, Q>(source.z, source.w, -source.x, -source.y);
    }
};
