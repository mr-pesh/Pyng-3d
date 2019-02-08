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
    UniquePointer<HeapAllocationPolicy, A> ptr1[] = {
        AllocateUnique<HeapAllocationPolicy, A>(1, 51),
        AllocateUnique<HeapAllocationPolicy, A>(2, 52),
        AllocateUnique<HeapAllocationPolicy, A>(3, 53),
        AllocateUnique<HeapAllocationPolicy, A>(4, 54),
        AllocateUnique<HeapAllocationPolicy, A>(5, 55),
    };

    UniquePointer<StackAllocationPolicy, A> ptr2[] = {
        AllocateUnique<StackAllocationPolicy, A>(6, 56),
        AllocateUnique<StackAllocationPolicy, A>(7, 57),
        AllocateUnique<StackAllocationPolicy, A>(8, 58),
        AllocateUnique<StackAllocationPolicy, A>(9, 59),
        AllocateUnique<StackAllocationPolicy, A>(10, 60),
    };

    printF(ptr1);
    printF(ptr2);

    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
