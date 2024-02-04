#pragma once

#include <set>
#include <string>
#include <vector>

class ScratchCard
{
public:
    void Parse(const std::string &line);
    size_t CalculatePoints() const;

private:
    std::set<size_t> winningNumbers;
    std::vector<size_t> myNumbers;
};

class ScratchCards
{
public:
    void Load(const std::string &filename);
    std::size_t CalculatePoints() const;

private:
    std::vector<ScratchCard> scratchCards;
};