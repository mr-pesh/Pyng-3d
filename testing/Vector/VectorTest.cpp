#include <gtest/gtest.h>

#include <Math/Matrix.h>
#include <Math/Vector.h>

#include <variant>

class VectorUnitTest : public testing::Test {
};

TEST_F(VectorUnitTest, MultiplicationTest)
{
    using VectorVariant = std::variant<Vector<int32_t,3>, Vector<float_t,3>, Vector<uint32_t,3>>;

    const VectorVariant vectors[] = {
        Vector<int32_t,3>{ 7, 9, 5 },
        Vector<float_t,3>{ 1.f, 2.f, 3.f },
        Vector<uint32_t,3>{ 89u, 46u, 101u },
    };

    #ifndef __GL_MATH_LIBRARY
    const std::variant<Matrix<float_t,3,3>> matrices[] = {
        Matrix<int32_t,3,3>{ 21, -76, -8, 1, 0, 31, 91, 6, 4 },
        Matrix<float_t,3,3>{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f },
        Matrix<uint32_t,3,3>{ 53u, 20u, 99u, 35u, 3u, 41u, 90u, 33u, 222u }
    #else
    const std::variant<Matrix<int32_t,3,3>, Matrix<float_t,3,3>, Matrix<uint32_t,3,3>> matrices[] = {
        Matrix<int32_t,3,3>{ 21, 1, 91, -76, 0, 6, -8, 31, 4 },
        Matrix<float_t,3,3>{ 1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f },
        Matrix<uint32_t,3,3>{ 53u, 35u, 90u, 20u, 3u, 33u, 99u, 41u, 222u }
    #endif
    };

    const VectorVariant expected[] = {
        Vector<int32_t,3>{ 611, -502, 243 },
        Vector<float_t,3>{ 30.f, 36.f, 42.f },
        Vector<uint32_t,3>{ 15417u, 5251u, 33119u }
    };

    for (unsigned i = 0; i < std::size(vectors); ++i)
    {
        std::visit([](auto &&vector, auto &&matrix, auto &&expect)
        {
            const auto result = vector * matrix;

            ASSERT_TRUE(std::equal(
                            std::begin(result), std::end(result), std::begin(expect), std::end(expect)
                        ));
        },
        vectors[i], matrices[i], expected[i]);
    };
}

TEST_F(VectorUnitTest, AngleEvaluationTest)
{
    using VectorVariant = std::variant<Vector<int32_t, 3>, Vector<float_t, 3>, Vector<uint32_t, 3>>;

    const VectorVariant vectors1[] = {
        Vector<float_t,3>{ 7.f, 9.f, 5.f },
        Vector<uint32_t,3>{ 7u, 9u, 5u },
    };

    const VectorVariant vectors2[] = {
        Vector<float_t,3>{ 1.f, 2.f, 3.f },
        Vector<uint32_t,3>{ 1u, 2u, 3u }
    };

    for (unsigned i = 0; i < 3; ++i)
    {
        std::visit([](const auto &vec1, const auto &vec2)
        {
            const auto angle = VectorAngle::Angle(vec1, vec2);
            const auto pi_2_ = VectorAngle::Angle(vec1, CrossProduct(vec1, vec2));

            ASSERT_NEAR(XMVectorGetX(angle), 0.53811252, 0.0001);
            ASSERT_NEAR(XMVectorGetX(pi_2_), 1.57079625, 0.0001);

        }, vectors1[i], vectors2[i]);
    }

    const auto vec3 = Vector<float_t, 3>{ 0.7f, 0.9f, 0.5f };
    const auto vec4 = Vector<float_t, 3>{ 0.1f, 0.2f, 0.3f };

    const auto angle = VectorAngle::OrientedAngle(vec3, vec4);
    const auto pi_2_ = VectorAngle::OrientedAngle(vec3, CrossProduct(vec3, vec4));

    ASSERT_NEAR(XMVectorGetX(angle), 1.15927947, 0.0001);
    ASSERT_NEAR(XMVectorGetX(pi_2_), 1.57079625, 0.0001);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
