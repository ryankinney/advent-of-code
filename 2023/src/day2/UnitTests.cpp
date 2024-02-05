#include <gtest/gtest.h>
#include "GameDocument.h"

namespace
{
    void ExpectExampleGame1(const Game &game)
    {
        const std::vector<Game::Set> &sets = game.GetSets();
        EXPECT_EQ(1, game.GetIDNumber());
        EXPECT_EQ(3, sets.size());
        EXPECT_EQ(4, sets[0].numRed);
        EXPECT_EQ(0, sets[0].numGreen);
        EXPECT_EQ(3, sets[0].numBlue);
        EXPECT_EQ(1, sets[1].numRed);
        EXPECT_EQ(2, sets[1].numGreen);
        EXPECT_EQ(6, sets[1].numBlue);
        EXPECT_EQ(0, sets[2].numRed);
        EXPECT_EQ(2, sets[2].numGreen);
        EXPECT_EQ(0, sets[2].numBlue);    
    }

    void ExpectExampleGame5(const Game &game)
    {
        const std::vector<Game::Set> &sets = game.GetSets();
        EXPECT_EQ(5, game.GetIDNumber());
        EXPECT_EQ(2, sets.size());
        EXPECT_EQ(6, sets[0].numRed);
        EXPECT_EQ(3, sets[0].numGreen);
        EXPECT_EQ(1, sets[0].numBlue);
        EXPECT_EQ(1, sets[1].numRed);
        EXPECT_EQ(2, sets[1].numGreen);
        EXPECT_EQ(2, sets[1].numBlue);         
    }

    void ExpectInputGame1(const Game &game)
    {
        const std::vector<Game::Set> &sets = game.GetSets();
        EXPECT_EQ(1, game.GetIDNumber());
        EXPECT_EQ(4, sets.size());
        EXPECT_EQ(12, sets[0].numRed);
        EXPECT_EQ(2, sets[0].numGreen);
        EXPECT_EQ(5, sets[0].numBlue);
        EXPECT_EQ(9, sets[1].numRed);
        EXPECT_EQ(6, sets[1].numGreen);
        EXPECT_EQ(4, sets[1].numBlue);
        EXPECT_EQ(10, sets[2].numRed);
        EXPECT_EQ(2, sets[2].numGreen);
        EXPECT_EQ(5, sets[2].numBlue);
        EXPECT_EQ(9, sets[3].numRed);
        EXPECT_EQ(0, sets[3].numGreen);
        EXPECT_EQ(8, sets[3].numBlue);
    }

    void ExpectInputGame100(const Game &game)
    {
        const std::vector<Game::Set> &sets = game.GetSets();
        EXPECT_EQ(100, game.GetIDNumber());
        EXPECT_EQ(6, sets.size());
        EXPECT_EQ(1, sets[0].numRed);
        EXPECT_EQ(5, sets[0].numGreen);
        EXPECT_EQ(0, sets[0].numBlue);
        EXPECT_EQ(1, sets[1].numRed);
        EXPECT_EQ(6, sets[1].numGreen);
        EXPECT_EQ(0, sets[1].numBlue);
        EXPECT_EQ(1, sets[2].numRed);
        EXPECT_EQ(6, sets[2].numGreen);
        EXPECT_EQ(6, sets[2].numBlue);
        EXPECT_EQ(2, sets[3].numRed);
        EXPECT_EQ(1, sets[3].numGreen);
        EXPECT_EQ(6, sets[3].numBlue);
        EXPECT_EQ(1, sets[4].numRed);
        EXPECT_EQ(4, sets[4].numGreen);
        EXPECT_EQ(8, sets[4].numBlue);
        EXPECT_EQ(0, sets[5].numRed);
        EXPECT_EQ(8, sets[5].numGreen);
        EXPECT_EQ(5, sets[5].numBlue);
    }
}

TEST(Game, ParseLine)
{
    Game game;
    game.ParseLine("Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green");
    ExpectExampleGame1(game);
}

TEST(GameDocument, Examples)
{
    GameDocument gameDocument;
    gameDocument.Load("example.txt");

    EXPECT_EQ(5, gameDocument.GetNumGames());
    ExpectExampleGame1(gameDocument.GetGame(0));
    ExpectExampleGame5(gameDocument.GetGame(4));

    gameDocument.CalculateResults();
    EXPECT_EQ(8, gameDocument.GetSumOfPossibleGames());
    EXPECT_EQ(2286, gameDocument.GetSumOfGamePowers());
}

TEST(GameDocument, Input)
{
    GameDocument gameDocument;
    gameDocument.Load("input.txt");
    EXPECT_EQ(100, gameDocument.GetNumGames());
    ExpectInputGame1(gameDocument.GetGame(0));
    ExpectInputGame100(gameDocument.GetGame(99));

    gameDocument.CalculateResults();
    EXPECT_EQ(2600, gameDocument.GetSumOfPossibleGames());
    EXPECT_EQ(86036, gameDocument.GetSumOfGamePowers());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}