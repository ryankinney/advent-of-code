#include <gtest/gtest.h>
#include "ScratchCards.h"

TEST(ScratchCards, Examples)
{
    ScratchCards scratchCards;
    scratchCards.Load("example.txt");
    scratchCards.CalculateNumMatches();
    scratchCards.CalculateNumCopies();
    EXPECT_EQ(scratchCards.GetPoints(), 13);
    EXPECT_EQ(scratchCards.GetTotalScratchCards(), 30);
}

TEST(ScratchCards, Input)
{
    ScratchCards scratchCards;
    scratchCards.Load("input.txt");
    scratchCards.CalculateNumMatches();
    scratchCards.CalculateNumCopies();
    EXPECT_EQ(scratchCards.GetPoints(), 25010);
    EXPECT_EQ(scratchCards.GetTotalScratchCards(), 9924412);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}