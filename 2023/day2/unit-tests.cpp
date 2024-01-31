#include <gtest/gtest.h>
#include "parse.h"
#include "process.h"

namespace
{
    const char *examplesFilename = "/home/ryan/dev/advent-of-code/2023/day2/examples.txt";
    const char *inputFilename = "/home/ryan/dev/advent-of-code/2023/day2/input.txt";

    void ExpectExampleGame1(const Game &game)
    {
        EXPECT_EQ(1, game.idNumber);
        EXPECT_EQ(3, game.sets.size());
        EXPECT_EQ(4, game.sets[0].numRed);
        EXPECT_EQ(0, game.sets[0].numGreen);
        EXPECT_EQ(3, game.sets[0].numBlue);
        EXPECT_EQ(1, game.sets[1].numRed);
        EXPECT_EQ(2, game.sets[1].numGreen);
        EXPECT_EQ(6, game.sets[1].numBlue);
        EXPECT_EQ(0, game.sets[2].numRed);
        EXPECT_EQ(2, game.sets[2].numGreen);
        EXPECT_EQ(0, game.sets[2].numBlue);    
    }

    void ExpectExampleGame5(const Game &game)
    {
        EXPECT_EQ(5, game.idNumber);
        EXPECT_EQ(2, game.sets.size());
        EXPECT_EQ(6, game.sets[0].numRed);
        EXPECT_EQ(3, game.sets[0].numGreen);
        EXPECT_EQ(1, game.sets[0].numBlue);
        EXPECT_EQ(1, game.sets[1].numRed);
        EXPECT_EQ(2, game.sets[1].numGreen);
        EXPECT_EQ(2, game.sets[1].numBlue);         
    }

    void ExpectInputGame1(const Game &game)
    {
        EXPECT_EQ(1, game.idNumber);
        EXPECT_EQ(4, game.sets.size());
        EXPECT_EQ(12, game.sets[0].numRed);
        EXPECT_EQ(2, game.sets[0].numGreen);
        EXPECT_EQ(5, game.sets[0].numBlue);
        EXPECT_EQ(9, game.sets[1].numRed);
        EXPECT_EQ(6, game.sets[1].numGreen);
        EXPECT_EQ(4, game.sets[1].numBlue);
        EXPECT_EQ(10, game.sets[2].numRed);
        EXPECT_EQ(2, game.sets[2].numGreen);
        EXPECT_EQ(5, game.sets[2].numBlue);
        EXPECT_EQ(9, game.sets[3].numRed);
        EXPECT_EQ(0, game.sets[3].numGreen);
        EXPECT_EQ(8, game.sets[3].numBlue);
    }

    void ExpectInputGame100(const Game &game)
    {
        EXPECT_EQ(100, game.idNumber);
        EXPECT_EQ(6, game.sets.size());
        EXPECT_EQ(1, game.sets[0].numRed);
        EXPECT_EQ(5, game.sets[0].numGreen);
        EXPECT_EQ(0, game.sets[0].numBlue);
        EXPECT_EQ(1, game.sets[1].numRed);
        EXPECT_EQ(6, game.sets[1].numGreen);
        EXPECT_EQ(0, game.sets[1].numBlue);
        EXPECT_EQ(1, game.sets[2].numRed);
        EXPECT_EQ(6, game.sets[2].numGreen);
        EXPECT_EQ(6, game.sets[2].numBlue);
        EXPECT_EQ(2, game.sets[3].numRed);
        EXPECT_EQ(1, game.sets[3].numGreen);
        EXPECT_EQ(6, game.sets[3].numBlue);
        EXPECT_EQ(1, game.sets[4].numRed);
        EXPECT_EQ(4, game.sets[4].numGreen);
        EXPECT_EQ(8, game.sets[4].numBlue);
        EXPECT_EQ(0, game.sets[5].numRed);
        EXPECT_EQ(8, game.sets[5].numGreen);
        EXPECT_EQ(5, game.sets[5].numBlue);
    }
}

TEST(Game, ParseLine)
{
    const Game &game = ParseLine("Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green");
    ExpectExampleGame1(game);
}

TEST(Game, ParseExamples)
{
    const Games &games = ParseFile(examplesFilename);
    EXPECT_EQ(5, games.size());
    ExpectExampleGame1(games[0]);
    ExpectExampleGame5(games[4]);
}

TEST(Game, ParseInput)
{
    const Games &games = ParseFile(inputFilename);
    EXPECT_EQ(100, games.size());
    ExpectInputGame1(games[0]);
    ExpectInputGame100(games[99]);
}

TEST(Game, ProcessExamples)
{
    const Games &games = ParseFile(examplesFilename);
    const TotalResult &totalResult = ProcessGames(games);
    EXPECT_EQ(8, totalResult.sumOfPossibleGames);
    EXPECT_EQ(2286, totalResult.sumOfGamePowers);
}

TEST(Game, ProcessInput)
{
    const Games &games = ParseFile(inputFilename);
    const TotalResult &totalResult = ProcessGames(games);
    EXPECT_EQ(2600, totalResult.sumOfPossibleGames);
    EXPECT_EQ(86036, totalResult.sumOfGamePowers);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}