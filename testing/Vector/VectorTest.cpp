#include <gtest/gtest.h>

#include <Math/Matrix.h>
#include <Math/Vector.h>

#include <array>
#include <numeric>
#include <variant>

template <size_t length>
using VectorVariant = std::variant<Vector<int32_t, length>, Vector<float_t, length>, Vector<uint32_t, length>>;

template <size_t length>
using VariantsArray = std::array<VectorVariant<length>, 3>;

class VectorUnitTest : public testing::Test {
};

TEST_F(VectorUnitTest, TransformTest)
{
    const VectorVariant<3> vectors[] = {
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

    const VectorVariant<3> expected[] = {
        Vector<int32_t,3>{ 611, -502, 243 },
        Vector<float_t,3>{ 30.f, 36.f, 42.f },
        Vector<uint32_t,3>{ 15417u, 5251u, 33119u }
    };

    for (uint32_t i = 0; i < std::size(vectors); ++i)
    {
        std::visit([](auto &&vector, auto &&matrix, auto &&expect)
        {
            const auto result = vector * matrix;

            ASSERT_TRUE(std::equal(std::begin(expect), std::end(expect), std::begin(result)));
        },
        vectors[i], matrices[i], expected[i]);
    };
}

TEST_F(VectorUnitTest, VectorCompareTest)
{
    using TestType = std::variant<VariantsArray<2>, VariantsArray<3>, VariantsArray<4>>;

    const TestType variants[] = {
        VariantsArray<2>{ ivec2{ 7, 9 }, fvec2{ 1.f, 2.f }, uvec2{ 89u, 46u } },
        VariantsArray<3>{ ivec3{ 7, 9, 5 }, fvec3{ 1.f, 2.f, 3.f }, uvec3{ 89u, 46u, 101u } },
        VariantsArray<4>{ ivec4{ 7, 9, 5, 0 }, fvec4{ 1.f, 2.f, 3.f, 0.f }, uvec4{ 89u, 46u, 101u, 0u } },
    };

    for (const auto &array : variants)
    {
        std::visit([](auto &&variantArray)
        {
            for (auto &&variant : variantArray)
            {
                std::visit([](auto &&vec1)
                {
                    // Equal
                    ASSERT_TRUE(vec1 == vec1);
                    ASSERT_FALSE(vec1 == Normalize(vec1));

                    // NotEqual
                    ASSERT_TRUE(vec1 != Normalize(vec1));
                    ASSERT_FALSE(vec1 != vec1);
                    
                    // GreaterOrEqual
                    ASSERT_TRUE(vec1 >= vec1);
                    ASSERT_TRUE(vec1 >= Normalize(vec1));

                    // Greater
                    // TODO: Replace Normalize function with devision by 2 
                    //ASSERT_TRUE(vec1 > Normalize(vec1));
                    ASSERT_FALSE(vec1 > vec1);

                    // LessOrEqual
                    ASSERT_TRUE(vec1 <= vec1);
                    ASSERT_FALSE(vec1 <= Normalize(vec1));

                    // Less
                    ASSERT_FALSE(vec1 < vec1);
                    ASSERT_FALSE(vec1 < Normalize(vec1));
                },
                variant);
            }
        }, array);
    }
}

TEST_F(VectorUnitTest, AngleFunctionsTest)
{
    {
        const auto vec1 = Vector<int32_t, 3>{ 7, 9, 5 };
        const auto vec2 = Vector<int32_t, 3>{ 1, 2, 3 };

        const auto angle = AngleBetweenVectors(vec1, vec2);
        const auto pi_2_ = AngleBetweenVectors(vec1, CrossProduct(vec1, vec2));

        ASSERT_NEAR(VectorGetX(angle), 0.53811252, 0.0001);
        ASSERT_NEAR(VectorGetX(pi_2_), 1.57079625, 0.0001);
    }
    {
        const auto vec1 = Vector<float_t, 3>{ 0.7f, 0.9f, 0.5f };
        const auto vec2 = Vector<float_t, 3>{ 0.1f, 0.2f, 0.3f };

        const auto angle = AngleBetweenNormals(vec1, vec2);
        const auto pi_2_ = AngleBetweenNormals(vec1, CrossProduct(vec1, vec2));

        ASSERT_NEAR(VectorGetX(angle), 1.15927947, 0.0001);
        ASSERT_NEAR(VectorGetX(pi_2_), 1.57079625, 0.0001);
    }
}

TEST_F(VectorUnitTest, VectorGeometryFunctions)
{
    const VectorVariant<3> args[] =
    {
        Vector<int32_t,3>{ 4, 3, 5 }, Vector<float_t,3>{ 4.f, 3.f, 5.f }, // Vector<uint32_t,3>{ 4u, 3u, 5u }
    };

    for (auto &&variant : args)
    {
        std::visit([](auto &&vec1)
        {
            using VectorType = std::decay_t<decltype(vec1)>;

            // ClampLength
            {
                auto result = ClampLength(vec1, 1.f, 10.f);

                ASSERT_TRUE(
                    std::equal(std::begin(vec1), std::end(vec1), std::begin(result), [](auto &&lhs, auto &&rhs) {
                        return std::abs(lhs - rhs) < 0.00001;
                    })
                );
            }
            // CrossProduct
            {
                VectorType vec2;
                std::iota(std::begin(vec2), std::end(vec2), decltype(VectorGetX(vec2))(0));

                auto result = CrossProduct(vec1, vec2);
                
                // manually calculate the cross-product of two vectors
                VectorType expect = [](auto &&v1, auto &&v2)
                {
                    if constexpr (is2dVector<VectorType>)
                    {
                        return VectorType{ (v1.x * v2.y) - (v1.y * v2.x), (v1.x * v2.y) - (v1.y * v2.x) };
                    }
                    else if (is3dVector<VectorType>)
                    {
                        return VectorType{ (v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x) };
                    }
                } (vec1, vec2);

                ASSERT_TRUE(
                    std::equal(std::begin(expect), std::end(expect), std::begin(result), [](auto &&lhs, auto &&rhs) {
                        return std::abs(lhs - rhs) < 0.00001;
                    })
                );
            }
            // DotProduct
            {
                ASSERT_FLOAT_EQ(VectorGetX(DotProduct(vec1, OrthogonalVector(vec1))), 0.f);
            }
            // InBounds
            {
                ASSERT_TRUE(InBounds(vec1, VectorType{ 5, 10, 6 }));
                ASSERT_TRUE(!InBounds(vec1, VectorType{ 1, 1, 1 }));
            }
            // Length
            {
                ASSERT_NEAR(VectorGetX(Length(vec1)),
                    // manually count the square root of a sum of each component of the vector in power of 2
                    std::sqrt(std::accumulate(std::begin(vec1), std::end(vec1), 0., [](auto &&acc, auto &&value) {
                        return acc + std::pow(value, 2);
                    }))
                , 0.00001);
            }
            // LengthSq
            {
                ASSERT_NEAR(VectorGetX(LengthSq(vec1)),
                    // manually count the sum of all component of the vector in power of 2
                    std::accumulate(std::begin(vec1), std::end(vec1), 0., [](auto &&acc, auto &&value) {
                        return acc + std::pow(value, 2);
                    })
                , 0.00001);

                ASSERT_FLOAT_EQ(std::pow(VectorGetX(Length(vec1)), 2), VectorGetX(LengthSq(vec1)));
            }
            // Normalize
            {
                const auto result = Normalize(vec1);
                const auto length = Length(vec1);

                float expect[sizeof(VectorType) / sizeof(float_t)];

                std::transform(std::begin(vec1), std::end(vec1), std::begin(expect), [vLength = VectorGetX(length)](auto &&comp) {
                    return comp / vLength;
                });

                ASSERT_TRUE(
                    std::equal(std::begin(expect), std::end(expect), std::begin(result), [](auto &&lhs, auto &&rhs) {
                        return std::abs(lhs - rhs) < 0.00001;
                    })
                );
            }
            // LinePointDistance
            {
                VectorType vec2, vec3;
                std::fill(std::begin(vec2), std::end(vec2), decltype(VectorGetX(vec2))(0));
                std::fill(std::begin(vec3), std::end(vec3), decltype(VectorGetX(vec3))(1));

                ASSERT_FLOAT_EQ(VectorGetX(LinePointDistance(vec1, vec2, vec3)), 0.346410155f);
            }
            // OrthogonalVector
            {
                ASSERT_FLOAT_EQ(VectorGetX(DotProduct(vec1, OrthogonalVector(vec1))), 0);
            }
            // ReciprocalLength
            {
                ASSERT_NEAR(
                    VectorGetX(ReciprocalLength(vec1)), 1.f / VectorGetX(Length(vec1))
                , 0.00001);
            }
            // Reflect
            {
                VectorType vec2;
                std::fill(std::begin(vec2), std::end(vec2), decltype(VectorGetX(vec2))(1));

                auto result = Reflect(vec1, VectorType{ 1, 1, 1 });
                
                float expect[] = { -20, -21, -19 };

                ASSERT_TRUE(
                    std::equal(std::begin(expect), std::end(expect), std::begin(result), [](auto &&lhs, auto &&rhs) {
                        return std::abs(lhs - rhs) < 0.00001;
                    })
                );
            }
            // Refract
            {
                VectorType vec2;
                std::fill(std::begin(vec2), std::end(vec2), decltype(VectorGetX(vec2))(1));

                auto result = Refract(vec1, vec2, 0.5f);

                float expect[] = { -10.062f, -10.562f, -9.562f };

                ASSERT_TRUE(
                    std::equal(std::begin(expect), std::end(expect), std::begin(result), [](auto &&lhs, auto &&rhs) {
                        return std::abs(lhs - rhs) < 0.001;
                    })
                );
            }
        },
        variant);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
