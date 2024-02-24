#include <gtest/gtest.h>
#include "AlmanacParser.h"

TEST(Almanac, Example)
{
    Almanac almanac;
    AlmanacFileParser(almanac).Load("example.txt");
    EXPECT_EQ(almanac.CalculateMinLocation(), 35);
}

TEST(Almanac, Input)
{
    Almanac almanac;
    AlmanacFileParser(almanac).Load("input.txt");
    EXPECT_EQ(almanac.CalculateMinLocation(), 322500873);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
