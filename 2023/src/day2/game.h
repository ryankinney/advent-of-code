#pragma once

#include <string>
#include <vector>

struct Set
{
    size_t numRed = 0;
    size_t numGreen = 0;
    size_t numBlue = 0;
};

struct Game
{
    int idNumber = 0;
    std::vector<Set> sets;
};

typedef std::vector<Game> Games;