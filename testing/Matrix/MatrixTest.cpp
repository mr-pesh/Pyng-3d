#include <gtest/gtest.h>

#include <Math/Matrix.h>
#include <Math/Vector.h>

#include <variant>

class MatrixUnitTest : public testing::Test {
};

TEST_F(MatrixUnitTest, MultiplicationTest)
{
    using VectorVariant = std::variant<Vector<int32_t,3>, Vector<float_t,3>, Vector<uint32_t,3>>;

    const VectorVariant vectors[] = {
        Vector<int32_t,3>{ 1, 2, 3 },
        Vector<float_t,3>{ 1.f, 2.f, 3.f },
        Vector<uint32_t,3>{ 1u, 2u, 3u },
    };

    #ifndef __GL_MATH_LIBRARY
    std::variant<Matrix<float_t,3,3>> matrices[] = {
        Matrix<int32_t,3,3>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 },
        Matrix<float_t,3,3>{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f },
        Matrix<uint32_t,3,3>{ 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u }
    #else
    std::variant<Matrix<int32_t,3,3>, Matrix<float_t,3,3>, Matrix<uint32_t,3,3>> matrices[] = {
        Matrix<int32_t, 3, 3> { 1, 4, 7, 2, 5, 8, 3, 6, 9 },
        Matrix<float, 3, 3> { 1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f },
        Matrix<uint32_t, 3, 3> { 1u, 4u, 7u, 2u, 5u, 8u, 3u, 6u, 9u }
    #endif
    };

    const VectorVariant expect[] = {
        Vector<int32_t,3>{ 30, 36, 42 },
        Vector<float_t,3>{ 30.f, 36.f, 42.f },
        Vector<uint32_t,3>{ 30u, 36u, 42u }
    };

    {
        auto matrix = std::begin(matrices);

        for (auto variant = std::begin(vectors), expected = std::begin(expect); variant != std::end(vectors); ++variant, ++expected)
        {
            std::visit([](auto &&vector, auto &&matrix, auto &&expected)
            {
                const auto result = vector * matrix;

                ASSERT_TRUE(std::equal(
                                std::begin(result), std::end(result), std::begin(expected), std::end(expected)
                            ));
            },
            *variant, *matrix, *expected);
            ++matrix;
        };
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
