#include "ScratchCards.h"

#include <fstream>
#include <sstream>

#include <iostream>

void ScratchCard::ParseLine(const std::string &line)
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
        m_winningNumbers.insert(currentWinningNumber);
    }

    // Parse my numbers
    size_t currentMyNumber = 0;
    while (in >> currentMyNumber)
        m_myNumbers.push_back(currentMyNumber);
}

void ScratchCard::CalculateNumMatches()
{
    m_numMatches = 0;
    for (const size_t myNumber : m_myNumbers)
        if (m_winningNumbers.find(myNumber) != m_winningNumbers.end())
            m_numMatches++;   
}

size_t ScratchCard::GetPoints() const
{
    return m_numMatches == 0 ? 0 : 1 << (m_numMatches - 1);
}

void ScratchCards::CalculateNumMatches()
{
    for (size_t index = 0; index < GetNumLineParsers(); index++)
        GetLineParser<ScratchCard>(index).CalculateNumMatches();
}

void ScratchCards::CalculateNumCopies()
{
    for (size_t outerIndex = 0; outerIndex < GetNumLineParsers(); outerIndex++)
    {
        ScratchCard &outerScratchCard = GetLineParser<ScratchCard>(outerIndex);
        const size_t numMatches = outerScratchCard.GetNumMatches();
        if (numMatches == 0)
            continue;

        if (outerIndex + 1 < GetNumLineParsers())
        {
            for (size_t innerIndex = outerIndex + 1; innerIndex < outerIndex + numMatches + 1 && innerIndex < GetNumLineParsers(); innerIndex++)
                GetLineParser<ScratchCard>(innerIndex).IncrementNumCopies(outerScratchCard.GetNumCopies());
        }
        //std::cout << "-----Round " << outerIndex + 1 << "-----" << std::endl;
        //PrintScratchCards();
    }
}

void ScratchCards::PrintScratchCards() const
{
    for (size_t index = 0; index < GetNumLineParsers(); index++)
    {
        const ScratchCard &scratchCard = GetLineParser<ScratchCard>(index);
        std::cout << index + 1 << ": " << scratchCard.GetNumMatches() << ',' << scratchCard.GetNumCopies() << std::endl;
    }
}

size_t ScratchCards::GetPoints() const
{
    size_t points = 0;
    for (size_t index = 0; index < GetNumLineParsers(); index++)
        points += GetLineParser<ScratchCard>(index).GetPoints();
    return points;
}

size_t ScratchCards::GetTotalScratchCards() const
{
    size_t totalScratchCards = 0;
    for (size_t index = 0; index < GetNumLineParsers(); index++)
        totalScratchCards += GetLineParser<ScratchCard>(index).GetNumCopies();
    return totalScratchCards;
}