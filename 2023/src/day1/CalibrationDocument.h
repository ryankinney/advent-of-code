#pragma once

#include "FileParser.h"

class Calibration : public LineParser
{
public:
    size_t GetValue() const { return 10*m_firstDigit + m_lastDigit; }

protected:
    size_t m_firstDigit = 0;
    size_t m_lastDigit = 0;
};

class P1Calibration : public Calibration
{
public:
    void ParseLine(const std::string &line) override;
};

class P2Calibration : public Calibration
{
public:
    void ParseLine(const std::string &line) override;
};

class CalibrationDocument : public FileParser
{
public:
    CalibrationDocument(std::unique_ptr<LineParserFactoryBase> lineParserFactory) : FileParser(std::move(lineParserFactory)) {}

    size_t GetSum() const;
};