#include <gtest/gtest.h>

#include <vector>
#include <string>

#include <Utils/MatrixIterator.h>

class MatrixIteratorUnitTest : public testing::Test {
};

TEST_F(MatrixIteratorUnitTest, 2D_STL_iterator)
{
    std::vector<std::string> m1 =
    {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    auto i = Pyng::begin<Pyng::Horizontal>(m1);

    ASSERT_TRUE((*i) == 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
