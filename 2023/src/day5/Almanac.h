#pragma once

#include "FileParser.h"

class AlamacLineParser : public LineParser
{
public:
    virtual void ParseLine(const std::string &line);
};

class Almanac : public FileParser
{
public:
    Almanac() : FileParser(std::unique_ptr<LineParserFactoryBase>(new LineParserFactory<AlamacLineParser>)) {}

private:
    enum ExpectedToken
    {
        Seeds
    };

    ExpectedToken m_nextToken = Seeds;
};