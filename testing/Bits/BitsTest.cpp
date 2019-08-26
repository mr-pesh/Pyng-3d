#include <gtest/gtest.h>
#include <Utils/Bits.h>

class BitOperationsUnitTest : public testing::Test {
};

TEST_F(BitOperationsUnitTest, BtInstructionsTest)
{
    long flags = 0;
    long oldValues[4];

    oldValues[1] = bittestandset(&flags, 1);

    ASSERT_EQ(flags, 0x2);

    oldValues[2] = bittestandset(&flags, 2);

    ASSERT_EQ(flags, 0x6);

    oldValues[3] = bittestandset(&flags, 3);

    ASSERT_EQ(flags, 0xe);

    oldValues[3] = bittestandreset(&flags, 3);

    ASSERT_EQ(flags, 0x6);

    bittestandchange(&flags, 1);

    ASSERT_EQ(flags, 0x4);

    if (oldValues[2])
        oldValues[2] = bittestandset(&flags, 2);
    else
        oldValues[2] = bittestandreset(&flags, 2);

    ASSERT_EQ(flags, 0x0);
}

TEST_F(BitOperationsUnitTest, BitTest)
{
    uint8_t bits[32];

    long nBit;

    static long num = 78002;

    for (nBit = 0; nBit < 31; nBit++)
    {
        bits[nBit] = bittest(&num, nBit);
    }

    std::stringstream ss;

    while (nBit--)
    {
        ss << static_cast<bool>(bits[nBit]);
    }

    ASSERT_EQ(ss.str(), "0000000000000010011000010110010");
}

TEST_F(BitOperationsUnitTest, CountLeadingZerosTest)
{
    {
        unsigned short data[] = { 0, 0xFF, 0xFFFF }, result[] = { 16, 8, 0 };

        ASSERT_TRUE(
            std::equal(std::begin(data), std::end(data), std::begin(result), [](auto &&value, auto &&count) {
                return clz(value) == count;
            })
        );
    }
    {
        unsigned int data[] = { 0, 0xFF, 0xFFFF, 0xFFFFFFFF }, result[] = { 32, 24, 16, 0 };

        ASSERT_TRUE(
            std::equal(std::begin(data), std::end(data), std::begin(result), [](auto &&value, auto &&count) {
                return clz(value) == count;
            })
        );
    }
    {
        unsigned long long data[] = { 0, 0xFF, 0xFFFF, 0xFFFFFFFF, 0xFFFFFFFFFFFFFFFF }, result[] = { 64, 56, 48, 32, 0 };

        ASSERT_TRUE(
            std::equal(std::begin(data), std::end(data), std::begin(result), [](auto &&value, auto &&count) {
                return clz(value) == count;
            })
        );
    }
}

TEST_F(BitOperationsUnitTest, PopcountTest)
{
    {
        unsigned short data[] = { 0, 0xFF, 0xFFFF }, result[] = { 0, 8, 16 };

        ASSERT_TRUE(
            std::equal(std::begin(data), std::end(data), std::begin(result), [](auto value, auto count) {
                return popcount(value) == count;
            })
        );
    }
    {
        unsigned int data[] = { 0, 0xFF, 0xFFFF, 0xFFFFFFFF }, result[] = { 0, 8, 16, 32 };

        ASSERT_TRUE(
            std::equal(std::begin(data), std::end(data), std::begin(result), [](auto value, auto count) {
                return popcount(value) == count;
            })
        );
    }
    {
        unsigned long long data[] = { 0, 0xFF, 0xFFFF, 0xFFFFFFFF, 0xFFFFFFFFFFFFFFFF }, result[] = { 0, 8, 16, 32, 64 };

        ASSERT_TRUE(
            std::equal(std::begin(data), std::end(data), std::begin(result), [](auto value, auto count) {
                return popcount(value) == count;
            })
        );
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
