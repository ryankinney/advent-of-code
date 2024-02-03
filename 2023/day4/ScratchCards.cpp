#include "ScratchCards.h"

#include <fstream>
#include <sstream>

#include <iostream>

void ScratchCard::Parse(const std::string &line)
{
    // An example line
    // Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
    std::istringstream in(line);
    
    // Parse the word 'Card'
    std::string theWordCard;
    in >> theWordCard;

    // Parse the card number
    size_t cardNumber = 0;
    in >> cardNumber;

    // Parse the colon
    in.get();

    // Parse the winning numbers
    std::string nextToken;
    while (in >> nextToken)
    {
        if (nextToken == "|")
            break;

        size_t currentWinningNumber = 0;
        std::istringstream currentWinningNumberIn(nextToken);
        currentWinningNumberIn >> currentWinningNumber;
        winningNumbers.insert(currentWinningNumber);
    }

    // Parse my numbers
    size_t currentMyNumber = 0;
    while (in >> currentMyNumber)
        myNumbers.push_back(currentMyNumber);
}

size_t ScratchCard::CalculatePoints() const
{
    size_t numMatches = 0;
    for (const size_t myNumber : myNumbers)
        if (winningNumbers.find(myNumber) != winningNumbers.end())
            numMatches++;
    return numMatches == 0 ? 0 : 1 << (numMatches - 1);
}

void ScratchCards::Load(const std::string &filename)
{
    std::string line;
    std::ifstream in(filename);
    while (std::getline(in, line))
    {
        ScratchCard scratchCard;
        scratchCard.Parse(line);
        scratchCards.push_back(scratchCard);
    }
}

std::size_t ScratchCards::CalculatePoints() const
{
    size_t points = 0;
    for (const ScratchCard &scratchCard : scratchCards)
        points += scratchCard.CalculatePoints();
    return points;
}