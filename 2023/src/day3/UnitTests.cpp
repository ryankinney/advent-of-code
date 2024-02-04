#include <gtest/gtest.h>
#include "Engine.h"

TEST(Engine, Examples)
{
    Engine engine;
    engine.Build("example.txt");
    EXPECT_EQ(engine.AddPartNumbers(), 4361);
    EXPECT_EQ(engine.AddGearRatios(), 467835);
}

TEST(Engine, Input)
{
    Engine engine;
    engine.Build("input.txt");
    EXPECT_EQ(engine.AddPartNumbers(), 519444);
    EXPECT_EQ(engine.AddGearRatios(), 74528807);   
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}