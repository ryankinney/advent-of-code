#pragma once

#include "game.h"

struct GameResult
{
    bool tooManyCubes = false;
    size_t power = 0;
};

struct TotalResult
{
    size_t sumOfPossibleGames = 0;
    size_t sumOfGamePowers = 0;
};

GameResult ProcessGame(const Game &game);
TotalResult ProcessGames(const Games &games);