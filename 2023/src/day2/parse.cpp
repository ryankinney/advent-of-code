#include "parse.h"

#include <fstream>
#include <sstream>

Game ParseLine(const std::string &line)
{
    // Example line is "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
    std::istringstream in(line);

    // Parse the word 'Game'
    std::string theWordGame;
    in >> theWordGame;

    // Parse the idNumber
    Game game;
    in >> game.idNumber;

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
            game.sets.push_back(set);
            break;
        }

        if (colorStrRemainder == ";")
        {
            game.sets.push_back(set);
            set = Set();
        }
    }
    return game;
}

Games ParseFile(const std::string &filename)
{
    std::string line;
    Games games;
    std::ifstream file(filename);
    while (std::getline(file, line))
    {
        const Game &game = ParseLine(line);
        games.push_back(game);
    }
    return games;
}