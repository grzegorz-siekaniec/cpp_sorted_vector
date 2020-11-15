#include "gtest/gtest.h"

TEST(SomeTest, DoesThis)
{
    ASSERT_FALSE(false);
}

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    const int ret_val = RUN_ALL_TESTS();
    return ret_val;
}