#pragma once

#include "FileParser.h"

class Game : public LineParser
{
public:
    struct Set
    {
        size_t numRed = 0;
        size_t numGreen = 0;
        size_t numBlue = 0;
    };

    void ParseLine(const std::string &line) override;
    size_t GetIDNumber() const { return m_idNumber; }
    const std::vector<Set> &GetSets() const { return m_sets; }

    void CalculateResults();
    bool HasTooManyCubes() const { return m_hasTooManyCubes; }
    size_t GetPower() const { return m_power; }

private:
    size_t m_idNumber = 0;
    std::vector<Set> m_sets;
    bool m_hasTooManyCubes = false;
    size_t m_power = 0;
};

class GameDocument : public FileParser
{
public:
    GameDocument() : FileParser(std::unique_ptr<LineParserFactoryBase>(new LineParserFactory<Game>)) {}

    size_t GetNumGames() const { return GetLineParsers().size(); }
    const Game &GetGame(const size_t index) const { return dynamic_cast<const Game &>(*GetLineParsers()[index]); }

    void CalculateResults();
    size_t GetSumOfPossibleGames() const { return m_sumOfPossibleGames; }
    size_t GetSumOfGamePowers() const { return m_sumOfGamePowers; }

private:
    size_t m_sumOfPossibleGames = 0;
    size_t m_sumOfGamePowers = 0;
};