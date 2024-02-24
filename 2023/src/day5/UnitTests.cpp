#include <gtest/gtest.h>
#include "AlmanacParser.h"

TEST(Almanac, Example)
{
    Almanac almanac;
    AlmanacFileParser(almanac).Load("example.txt");
    EXPECT_EQ(almanac.CalculateMinLocation(), 35);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
