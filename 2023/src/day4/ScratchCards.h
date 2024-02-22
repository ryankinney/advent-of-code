#pragma once

#include <set>
#include "FileParser.h"

class ScratchCard : public LineParser
{
public:
    void ParseLine(const std::string &line) override;
    void CalculateNumMatches();
    void IncrementNumCopies(const size_t amount) { m_numCopies += amount; }

    size_t GetNumMatches() const { return m_numMatches; }
    size_t GetPoints() const;
    size_t GetNumCopies() const { return m_numCopies; }

private:
    std::set<size_t> m_winningNumbers;
    std::vector<size_t> m_myNumbers;
    size_t m_numMatches = 0;
    size_t m_numCopies = 1;
};

class ScratchCards : public FileParser
{
public:
    ScratchCards() : FileParser(std::unique_ptr<LineParserFactoryBase>(new LineParserFactory<ScratchCard>)) {}

    void CalculateNumMatches();
    void CalculateNumCopies();

    void PrintScratchCards() const;
    size_t GetPoints() const;
    size_t GetTotalScratchCards() const;
};