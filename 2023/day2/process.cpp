#include "process.h"

GameResult ProcessGame(const Game &game)
{
    GameResult gameResult;
    size_t minRedCubes = 0, minBlueCubes = 0, minGreenCubes = 0;
    for (size_t setIndex = 0; setIndex < game.sets.size(); setIndex++)
    {
        const Set &set = game.sets[setIndex];
        if (!gameResult.tooManyCubes && set.numRed > 12 || set.numGreen > 13 || set.numBlue > 14)
            gameResult.tooManyCubes = true;
        minRedCubes = std::max(minRedCubes, set.numRed);
        minGreenCubes = std::max(minGreenCubes, set.numGreen);
        minBlueCubes = std::max(minBlueCubes, set.numBlue);
    }
    gameResult.power = minRedCubes * minGreenCubes * minBlueCubes;
    return gameResult;
}

TotalResult ProcessGames(const Games &games)
{
    TotalResult totalResult;
    for (size_t gameIndex = 0; gameIndex < games.size(); gameIndex++)
    {
        const Game &game = games[gameIndex];
        const GameResult &gameResult = ProcessGame(game);
        if (!gameResult.tooManyCubes)
            totalResult.sumOfPossibleGames += game.idNumber;
        totalResult.sumOfGamePowers += gameResult.power;
    }
    return totalResult;
}