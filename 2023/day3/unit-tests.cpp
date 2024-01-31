#include <gtest/gtest.h>
#include "part-numbers.h"

TEST(TestCase, Test)
{
    EXPECT_EQ(AddPartNumbers("../example.txt"), 4361);
    EXPECT_EQ(AddPartNumbers("../input.txt"), 519444);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}