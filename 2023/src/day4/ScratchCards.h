#pragma once

#include <set>
#include "FileParser.h"

class ScratchCard : public LineParser
{
public:
    void ParseLine(const std::string &line) override;

    size_t CalculatePoints() const;

private:
    std::set<size_t> winningNumbers;
    std::vector<size_t> myNumbers;
};

class ScratchCards : public FileParser
{
public:
    ScratchCards() : FileParser(std::unique_ptr<LineParserFactoryBase>(new LineParserFactory<ScratchCard>)) {}

    std::size_t CalculatePoints() const;
};