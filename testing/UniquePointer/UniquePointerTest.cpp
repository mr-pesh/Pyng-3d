#include <gtest/gtest.h>
#include <Utils/property.h>
#include <Utils/UniquePointer.h>


class UniquePointerUnitTest : public testing::Test {
};

class Foo {
    PROPERTY(uint32_t, A)
    PROPERTY(uint32_t, B)

public:
    Foo() = default;
    Foo(uint32_t a, uint32_t b) : _A(a), _B(b) { }
};

template <class T>
void printF(T &&ptr)
{
    for (auto&& p : ptr)
    {
        std::cout << "Address: " << &p << "\n[" << p->A() << ',' << p->B() << "]\n";
    }

    std::cout << std::flush;
}

TEST_F(UniquePointerUnitTest, ManageTest)
{
    UniquePointer<Foo, HeapAllocationPolicy> ptr1[] = {
        AllocateUnique<Foo, HeapAllocationPolicy>(1, 51),
        AllocateUnique<Foo, HeapAllocationPolicy>(2, 52),
        AllocateUnique<Foo, HeapAllocationPolicy>(3, 53),
        AllocateUnique<Foo, HeapAllocationPolicy>(4, 54),
        AllocateUnique<Foo, HeapAllocationPolicy>(5, 55),
    };

    UniquePointer<Foo, StackAllocationPolicy> ptr2[] = {
        AllocateUnique<Foo, StackAllocationPolicy>(6, 56),
        AllocateUnique<Foo, StackAllocationPolicy>(7, 57),
        AllocateUnique<Foo, StackAllocationPolicy>(8, 58),
        AllocateUnique<Foo, StackAllocationPolicy>(9, 59),
        AllocateUnique<Foo, StackAllocationPolicy>(10, 60),
    };

    printF(ptr1);
    printF(ptr2);

    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
