#pragma once

#include "Almanac.h"
#include "FileParser.h"

enum ExpectedToken
{
    ExpectingSeeds,
    ExpectingBlankLine,
    ExpectingMap,
    ExpectingMapRange
};

class AlmanacLineParser : public LineParser
{
public:
    void Init(const bool parseSeedsAsRange, const ExpectedToken expectedToken, Almanac &almanac);

    void ParseLine(const std::string &line) override;
    bool IsEmptyLine() const { return m_isEmptyLine; }

private:
    void ParseSeeds(const std::string &line);
    void ParseRangeMap(const std::string &line);
    void ParseRange(const std::string &line);

    ExpectedToken m_expectedToken = ExpectingSeeds;
    Almanac *m_almanac = nullptr;
    bool m_parseSeedsAsRange = false;
    bool m_isEmptyLine = false;
};

class AlmanacFileParser : public FileParser
{
public:
    AlmanacFileParser(const bool parseSeedsAsRange, Almanac &almanac);

protected:
    void OnBeginLine(LineParser &lineParser) override;
    void OnEndLine(LineParser &lineParser) override;

private:
    bool m_parseSeedsAsRange = false;
    ExpectedToken m_expectedToken = ExpectingSeeds;
    Almanac &m_almanac;
};