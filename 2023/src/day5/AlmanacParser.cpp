#include "AlmanacParser.h"

#include <iostream>
#include <sstream>

void AlmanacLineParser::Init(const bool parseSeedsAsRange, const ExpectedToken expectedToken, Almanac &almanac)
{
    m_parseSeedsAsRange = parseSeedsAsRange;
    m_expectedToken = expectedToken;
    m_almanac = &almanac;
}

void AlmanacLineParser::ParseSeeds(const std::string &line)
{
    // Example:
    // seeds: 79 14 55 13
    std::istringstream in(line);
    
    std::string theWordSeeds;
    in >> theWordSeeds;

    if (m_parseSeedsAsRange)
    {
        size_t seedStart = 0, seedSize = 0;
        while (in >> seedStart)
        {
            in >> seedSize;
            m_almanac->AddSeedRange(seedStart, seedSize);
        }
    }
    else
    {   
        size_t seed = 0;
        while (in >> seed)
            m_almanac->AddSeedRange(seed, 1);
    }
}

void AlmanacLineParser::ParseRangeMap(const std::string &line)
{
    // Example:
    // seed-to-soil map:
    std::istringstream in(line);

    std::string mapName;
    in >> mapName;
    const size_t firstDashPos = mapName.find('-');
    const size_t secondDashPos = mapName.rfind('-');
    const std::string &sourceCategory = mapName.substr(0, firstDashPos);
    const std::string &destinationCategory = mapName.substr(secondDashPos + 1);
    m_almanac->AddRangeMap(sourceCategory, destinationCategory);
}

void AlmanacLineParser::ParseRange(const std::string &line)
{
    // Example:
    // 50 98 2
    std::istringstream in(line);

    size_t destinationRangeStart = 0;
    in >> destinationRangeStart;
    if (!in)
    {   
        m_isEmptyLine = true;
    }
    else
    {
        size_t sourceRangeStart = 0, rangeLength = 0;
        in >> sourceRangeStart >> rangeLength;
        m_almanac->AddRange(destinationRangeStart, sourceRangeStart, rangeLength);
    }
}

void AlmanacLineParser::ParseLine(const std::string &line)
{
    switch (m_expectedToken)
    {
        case ExpectingSeeds:
            ParseSeeds(line);
            break;
        case ExpectingMap:
            ParseRangeMap(line);
            break;
        case ExpectingMapRange:
            ParseRange(line);
            break;
    }
}

AlmanacFileParser::AlmanacFileParser(const bool parseSeedsAsRange, Almanac &almanac) : 
    FileParser(std::unique_ptr<LineParserFactoryBase>(new LineParserFactory<AlmanacLineParser>)),
    m_parseSeedsAsRange(parseSeedsAsRange),
    m_almanac(almanac)
{
}

void AlmanacFileParser::OnBeginLine(LineParser &lineParser)
{
    dynamic_cast<AlmanacLineParser &>(lineParser).Init(m_parseSeedsAsRange, m_expectedToken, m_almanac);
}

void AlmanacFileParser::OnEndLine(LineParser &lineParser)
{
    switch (m_expectedToken)
    {
        case ExpectingSeeds:
            m_expectedToken = ExpectingBlankLine;
            break;
        case ExpectingBlankLine:
            m_expectedToken = ExpectingMap;
            break;
        case ExpectingMap:
            m_expectedToken = ExpectingMapRange;
            break;
        case ExpectingMapRange:
            if (dynamic_cast<AlmanacLineParser &>(lineParser).IsEmptyLine())
                m_expectedToken = ExpectingMap;
            break;
    }
}