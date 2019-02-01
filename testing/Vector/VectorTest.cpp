#include <gtest/gtest.h>

#include <Math/Matrix.h>
#include <Math/Vector.h>

#include <variant>

class VectorUnitTest : public testing::Test {
};

template <size_t length>
using VectorVariants = std::variant<Vector<int32_t, length>, Vector<float_t, length>, Vector<uint32_t, length>>;


TEST_F(VectorUnitTest, TransformTest)
{
    {
        const auto vector = Vector<int32_t, 3>{ 7, 9, 5 };
        const auto matrix =
#ifndef __GL_MATH_LIBRARY
            Matrix<int32_t, 3, 3>{ 21, -76, -8, 1, 0, 31, 91, 6, 4 };
#else
            Matrix<int32_t, 3, 3>{ 21, 1, 91, -76, 0, 6, -8, 31, 4 };
#endif
        const auto expected = Vector<int32_t, 3>{ 611, -502, 243 };

        const auto result = vector * matrix;

        ASSERT_TRUE(std::equal(
            std::begin(result), std::end(result), std::begin(expected), std::end(expected)
        ));
    }
    {
        const auto vector = Vector<float_t, 3>{ 1.f, 2.f, 3.f };
        const auto matrix =
#ifndef __GL_MATH_LIBRARY
            Matrix<float_t, 3, 3>{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
#else
            Matrix<float_t, 3, 3>{ 1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f };
#endif
        const auto expected = Vector<float_t, 3>{ 30.f, 36.f, 42.f };

        const auto result = vector * matrix;

        ASSERT_TRUE(std::equal(
            std::begin(result), std::end(result), std::begin(expected), std::end(expected)
        ));
    }
    {
        const auto vector = Vector<uint32_t, 3>{ 89u, 46u, 101u };
        const auto matrix =
#ifndef __GL_MATH_LIBRARY
            Matrix<uint32_t, 3, 3>{ 53u, 20u, 99u, 35u, 3u, 41u, 90u, 33u, 222u };
#else
            Matrix<uint32_t, 3, 3>{ 53u, 35u, 90u, 20u, 3u, 33u, 99u, 41u, 222u }
#endif
        const auto expected = Vector<uint32_t, 3>{ 15417u, 5251u, 33119u };

        const auto result = vector * matrix;

        ASSERT_TRUE(std::equal(
            std::begin(result), std::end(result), std::begin(expected), std::end(expected)
        ));
    }
}

TEST_F(VectorUnitTest, AngleFunctionsTest)
{
    {
        const auto vec1 = Vector<uint32_t, 3>{ 7u, 9u, 5u };
        const auto vec2 = Vector<uint32_t, 3>{ 1u, 2u, 3u };

        const auto angle = VectorAngle::AngleBetweenVectors(vec1, vec2);
        const auto pi_2_ = VectorAngle::AngleBetweenVectors(vec1, CrossProduct(vec1, vec2));

        ASSERT_NEAR(XMVectorGetX(angle), 0.53811252, 0.0001);
        ASSERT_NEAR(XMVectorGetX(pi_2_), 1.57079625, 0.0001);
    }
    {
        const auto vec1 = Vector<float_t, 3>{ 0.7f, 0.9f, 0.5f };
        const auto vec2 = Vector<float_t, 3>{ 0.1f, 0.2f, 0.3f };

        const auto angle = VectorAngle::AngleBetweenNormals(vec1, vec2);
        const auto pi_2_ = VectorAngle::AngleBetweenNormals(vec1, CrossProduct(vec1, vec2));

        ASSERT_NEAR(XMVectorGetX(angle), 1.15927947, 0.0001);
        ASSERT_NEAR(XMVectorGetX(pi_2_), 1.57079625, 0.0001);
    }
}

TEST_F(VectorUnitTest, VectorGeometryFunctions)
{
    const VectorVariants<3> args[] =
    {
        Vector<int32_t,3>{ 4, 3, 5 }, Vector<float_t,3>{ 4.f, 3.f, 5.f }, Vector<uint32_t,3>{ 4u, 3u, 5u }
    };

    for (auto &&variant : args)
    {
        std::visit([](auto &&vec1)
        {
            using VectorType = std::decay_t<decltype(vec1)>;

            // DotProduct
            DotProduct(vec1, Normalize(vec1));
            DotProduct(vec1, vec1);

            // Length
            ASSERT_NEAR(*std::begin(Length(vec1)),
                // manually count the square root of each component of the vector in power of 2
                std::sqrt(std::accumulate(std::begin(vec1), std::end(vec1), 0., [](auto &&acc, auto &&value) {
                    return acc + std::pow(value, 2);
                }))
            , 0.00001);

            // ReciprocalLength
            ASSERT_NEAR(
                // dirty hack to obtain the x component of the vector
                *std::begin(ReciprocalLength(vec1)), 1.f / *std::begin(Length(vec1))
            , 0.00001);

            // InBounds
            ASSERT_TRUE(InBounds(vec1, VectorType{5, 10, 6}));
            ASSERT_FALSE(InBounds(vec1, VectorType{1, 1, 1}));
        },
        variant);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
