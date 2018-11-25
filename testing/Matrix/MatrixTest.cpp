#include <gtest/gtest.h>

#include <Math/Matrix.h>
#include <Math/Vector.h>

class MatrixUnitTest : public testing::Test {
};

TEST_F(MatrixUnitTest, MultiplicationTest)
{
    auto v = Vector<float, 3> { 1.f, 2.f, 3.f };

    auto m = Matrix<float, 3, 3>
#ifndef __GL_MATH_LIBRARY
    { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
#else
    { 1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f };
#endif

    const Vector<float, 3> result = v * m;
    const float expect[] = { 30.f, 36.f, 42.f };

    ASSERT_TRUE(std::equal(
                    std::begin(result), std::end(result),
                    std::begin(expect), std::end(expect)
                ));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
