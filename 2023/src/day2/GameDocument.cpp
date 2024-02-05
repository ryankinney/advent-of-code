#include "GameDocument.h"

#include <sstream>

void Game::ParseLine(const std::string &line)
{
    // Example line is "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
    std::istringstream in(line);

    // Parse the word 'Game'
    std::string theWordGame;
    in >> theWordGame;

    // Parse the idNumber
    in >> m_idNumber;

    // Parse the colon
    std::string aColon;
    in >> aColon;

    Set set;
    while (true)
    {
        size_t quantity = 0;
        in >> quantity;

        std::string colorStr;
        in >> colorStr;

        std::string colorStrRemainder;
        if (colorStr.substr(0, 3) == "red")
        {
            set.numRed = quantity;
            colorStrRemainder = colorStr.substr(3);
        }
        else if (colorStr.substr(0, 4) == "blue")
        {
            set.numBlue = quantity;
            colorStrRemainder = colorStr.substr(4);
        }
        else if (colorStr.substr(0, 5) == "green")
        {
            set.numGreen = quantity;
            colorStrRemainder = colorStr.substr(5);
        }

        if (colorStrRemainder.empty())
        {
            m_sets.push_back(set);
            break;
        }

        if (colorStrRemainder == ";")
        {
            m_sets.push_back(set);
            set = Set();
        }
    }
}

void Game::CalculateResults()
{
    size_t minRedCubes = 0, minBlueCubes = 0, minGreenCubes = 0;
    for (size_t setIndex = 0; setIndex < m_sets.size(); setIndex++)
    {
        const Set &set = m_sets[setIndex];
        if (!m_hasTooManyCubes && set.numRed > 12 || set.numGreen > 13 || set.numBlue > 14)
            m_hasTooManyCubes = true;
        minRedCubes = std::max(minRedCubes, set.numRed);
        minGreenCubes = std::max(minGreenCubes, set.numGreen);
        minBlueCubes = std::max(minBlueCubes, set.numBlue);
    }
    m_power = minRedCubes * minGreenCubes * minBlueCubes;
}

void GameDocument::CalculateResults()
{
    for (LineParsers::iterator iter = m_lineParsers.begin(); iter != m_lineParsers.end(); iter++)
    {
        Game &game = dynamic_cast<Game &>(**iter);
        game.CalculateResults();
        if (!game.HasTooManyCubes())
            m_sumOfPossibleGames += game.GetIDNumber();
        m_sumOfGamePowers += game.GetPower();
    }
}