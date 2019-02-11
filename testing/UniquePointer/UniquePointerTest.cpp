#include <gtest/gtest.h>
#include <Utils/UniquePointer.h>

class UniquePointerUnitTest : public testing::Test {
};

struct A {
    A(uint32_t a_, uint32_t g_) : a(a_), g(g_) { }
    uint32_t a;
    uint32_t g;
};

template <class T>
void printF(const T &ptr)
{
    for (const auto &p : ptr) {
        std::cout << "Address: " << &(*p) << std::endl;
        std::cout << "[" << p->a << ',' << p->g << ']' << std::endl;
    }
}

TEST_F(UniquePointerUnitTest, ManageTest)
{
    UniquePointer<A, HeapAllocationPolicy> ptr1[] = {
        AllocateUnique<A, HeapAllocationPolicy>(1, 51),
        AllocateUnique<A, HeapAllocationPolicy>(2, 52),
        AllocateUnique<A, HeapAllocationPolicy>(3, 53),
        AllocateUnique<A, HeapAllocationPolicy>(4, 54),
        AllocateUnique<A, HeapAllocationPolicy>(5, 55),
    };

    UniquePointer<A, StackAllocationPolicy> ptr2[] = {
        AllocateUnique<A, StackAllocationPolicy>(6, 56),
        AllocateUnique<A, StackAllocationPolicy>(7, 57),
        AllocateUnique<A, StackAllocationPolicy>(8, 58),
        AllocateUnique<A, StackAllocationPolicy>(9, 59),
        AllocateUnique<A, StackAllocationPolicy>(10, 60),
    };

    printF(ptr1);
    printF(ptr2);

    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
