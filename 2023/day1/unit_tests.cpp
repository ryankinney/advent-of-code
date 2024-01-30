#include <gtest/gtest.h>
#include "calibration.h"

TEST(GetP1CalibrationValue, Examples)
{
    EXPECT_EQ(GetP1CalibrationValue("1abc2"), 12);
    EXPECT_EQ(GetP1CalibrationValue("pqr3stu8vwx"), 38);
    EXPECT_EQ(GetP1CalibrationValue("a1b2c3d4e5f"), 15);
    EXPECT_EQ(GetP1CalibrationValue("treb7uchet"), 77);
}

TEST(GetP1CalibrationValue, Input)
{
    // 55208
}

TEST(GetP2CalibrationValue, Examples)
{
    EXPECT_EQ(GetP2CalibrationValue("two1nine"), 29);
    EXPECT_EQ(GetP2CalibrationValue("eightwothree"), 83);
    EXPECT_EQ(GetP2CalibrationValue("abcone2threexyz"), 13);
    EXPECT_EQ(GetP2CalibrationValue("xtwone3four"), 24);
    EXPECT_EQ(GetP2CalibrationValue("4nineeightseven2"), 42);
    EXPECT_EQ(GetP2CalibrationValue("zoneight234"), 14);
    EXPECT_EQ(GetP2CalibrationValue("7pqrstsixteen"), 76);
}

TEST(GetP2CalibrationValue, Input)
{
    // 54578
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
