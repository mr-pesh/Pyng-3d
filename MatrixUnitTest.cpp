#include <gtest/gtest.h>

#include "Matrix.h"
#include "Vector.h"

class MatrixUnitTest : public testing::Test {
};

TEST_F(MatrixUnitTest, CreationTest)
{
    const Vector<float, 3> v{};
    const Matrix<float, 3, 3> m{};

    std::array<float, 9> arr = { 1.f, 2.f, 3.f, 4.f, 5.f, 5.f, 7.f, 8.f, 9.f };

    memcpy((void*)&m, (void*)&arr, std::size(arr));

    m.transpose();

    ASSERT_TRUE(m(1,1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
