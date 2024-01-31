#include <gtest/gtest.h>
#include "part1.h"
#include "part2.h"

namespace
{
    static const char *inputFilename = "../input.txt";
}

TEST(Part1, ExampleLines)
{
    EXPECT_EQ(P1::GetCalibrationValue("1abc2"), 12);
    EXPECT_EQ(P1::GetCalibrationValue("pqr3stu8vwx"), 38);
    EXPECT_EQ(P1::GetCalibrationValue("a1b2c3d4e5f"), 15);
    EXPECT_EQ(P1::GetCalibrationValue("treb7uchet"), 77);
}

TEST(Part1, TestFiles)
{
    EXPECT_EQ(P1::GetSum("../p1-examples.txt"), 142);
    EXPECT_EQ(P1::GetSum(inputFilename), 55208);
}

TEST(Part2, ExampleLines)
{
    EXPECT_EQ(P2::GetCalibrationValue("two1nine"), 29);
    EXPECT_EQ(P2::GetCalibrationValue("eightwothree"), 83);
    EXPECT_EQ(P2::GetCalibrationValue("abcone2threexyz"), 13);
    EXPECT_EQ(P2::GetCalibrationValue("xtwone3four"), 24);
    EXPECT_EQ(P2::GetCalibrationValue("4nineeightseven2"), 42);
    EXPECT_EQ(P2::GetCalibrationValue("zoneight234"), 14);
    EXPECT_EQ(P2::GetCalibrationValue("7pqrstsixteen"), 76);
}

TEST(Part2, TestFiles)
{
    EXPECT_EQ(P2::GetSum("../p2-examples.txt"), 281);
    EXPECT_EQ(P2::GetSum(inputFilename), 54578);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}