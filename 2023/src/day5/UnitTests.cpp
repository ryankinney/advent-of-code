#include <gtest/gtest.h>
#include "AlmanacParser.h"

TEST(Almanac, Part1Example)
{
    Almanac almanac;
    AlmanacFileParser(false, almanac).Load("example.txt");
    EXPECT_EQ(almanac.CalculateMinLocation(), 35);
}
TEST(Almanac, Part1Input)
{
    Almanac almanac;
    AlmanacFileParser(false, almanac).Load("input.txt");
    EXPECT_EQ(almanac.CalculateMinLocation(), 322500873);
}

TEST(Almanac, Part2Example)
{
    Almanac almanac;
    AlmanacFileParser(true, almanac).Load("example.txt");
    EXPECT_EQ(almanac.CalculateMinLocation(), 46);
}

TEST(Almanac, Part2Input)
{
    Almanac almanac;
    AlmanacFileParser(true, almanac).Load("input.txt");
    EXPECT_EQ(almanac.CalculateMinLocation(), 108956227);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}