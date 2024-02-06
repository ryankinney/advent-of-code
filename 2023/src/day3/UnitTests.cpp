#include <gtest/gtest.h>
#include "EngineSchematic.h"

TEST(EngineSchematic, Examples)
{
    EngineSchematic engineSchematic;
    engineSchematic.Load("example.txt");
    engineSchematic.FindPartNumbersAndGears();
    EXPECT_EQ(engineSchematic.CalculateSumOfPartNumbers(), 4361);
    EXPECT_EQ(engineSchematic.CalculateSumOfGearRatios(), 467835);
}

TEST(EngineSchematic, Input)
{
    EngineSchematic engineSchematic;
    engineSchematic.Load("input.txt");
    engineSchematic.FindPartNumbersAndGears();
    EXPECT_EQ(engineSchematic.CalculateSumOfPartNumbers(), 519444);
    EXPECT_EQ(engineSchematic.CalculateSumOfGearRatios(), 74528807);   
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}