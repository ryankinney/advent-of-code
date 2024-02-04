#include <gtest/gtest.h>
#include "CalibrationDocument.h"

namespace
{
    size_t GetP1CalibrationValue(const std::string &line)
    {
        P1Calibration calibration;
        calibration.ParseLine(line);
        return calibration.GetValue();
    }

    size_t GetP2CalibrationValue(const std::string &line)
    {
        P2Calibration calibration;
        calibration.ParseLine(line);
        return calibration.GetValue();
    }

    size_t GetP1Sum(const std::string &filename)
    {
        CalibrationDocument calibrationDocument(std::unique_ptr<LineParserFactoryBase>(new LineParserFactory<P1Calibration>));
        calibrationDocument.Load(filename);
        return calibrationDocument.GetSum();
    }

    size_t GetP2Sum(const std::string &filename)
    {
        CalibrationDocument calibrationDocument(std::unique_ptr<LineParserFactoryBase>(new LineParserFactory<P2Calibration>));
        calibrationDocument.Load(filename);
        return calibrationDocument.GetSum();
    }
}

TEST(P1Calibration, ExampleLines)
{
    EXPECT_EQ(GetP1CalibrationValue("1abc2"), 12);
    EXPECT_EQ(GetP1CalibrationValue("pqr3stu8vwx"), 38);
    EXPECT_EQ(GetP1CalibrationValue("a1b2c3d4e5f"), 15);
    EXPECT_EQ(GetP1CalibrationValue("treb7uchet"), 77);
}

TEST(P2Calibration, ExampleLines)
{
    EXPECT_EQ(GetP2CalibrationValue("two1nine"), 29);
    EXPECT_EQ(GetP2CalibrationValue("eightwothree"), 83);
    EXPECT_EQ(GetP2CalibrationValue("abcone2threexyz"), 13);
    EXPECT_EQ(GetP2CalibrationValue("xtwone3four"), 24);
    EXPECT_EQ(GetP2CalibrationValue("4nineeightseven2"), 42);
    EXPECT_EQ(GetP2CalibrationValue("zoneight234"), 14);
    EXPECT_EQ(GetP2CalibrationValue("7pqrstsixteen"), 76);
}

TEST(P1CalibrationDocument, Examples)
{
    EXPECT_EQ(GetP1Sum("p1-examples.txt"), 142);
}

TEST(P1CalibrationDocument, Input)
{
    EXPECT_EQ(GetP1Sum("input.txt"), 55208);
}

TEST(P2CalibrationDocument, Examples)
{
    EXPECT_EQ(GetP2Sum("p2-examples.txt"), 281);
}

TEST(P2CalibrationDocument, Input)
{
    EXPECT_EQ(GetP2Sum("input.txt"), 54578);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}