#pragma once

#include "game.h"

struct GameResult
{
    bool tooManyCubes = false;
    size_t power = 0;
};

struct TotalResult
{
    size_t sum = 0;
};

GameResult ProcessGame(const Game &game);
TotalResult ProcessGames(const Games &games);