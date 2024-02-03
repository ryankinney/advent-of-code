#include <gtest/gtest.h>
#include "ScratchCards.h"

TEST(ScratchCards, Examples)
{
    ScratchCards scratchCards;
    scratchCards.Load("../example.txt");
    EXPECT_EQ(scratchCards.CalculatePoints(), 13);
}

TEST(ScratchCards, Input)
{
    ScratchCards scratchCards;
    scratchCards.Load("../input.txt");
    EXPECT_EQ(scratchCards.CalculatePoints(), 25010);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}