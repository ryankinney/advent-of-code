#include "DocumentParser.h"

#include <sstream>

void DocumentLineParser::ParseLine(const std::string &line)
{
    // Example:
    // Time:      7  15   30
    // Distance:  9  40  200
    std::istringstream in(line);
    
    std::string label;
    in >> label;
    m_valueType = label == "Time:" ? Time : Distance;

    ParseValues(in);
}

void Part1LineParser::ParseValues(std::istream &in)
{
    size_t value = 0;
    while (in >> value)
        AddValue(value);
}

void Part2LineParser::ParseValues(std::istream &in)
{
    std::string str, valueStr;
    while (in >> str)
        valueStr += str;

    std::istringstream valueIn(valueStr);
    size_t value = 0;
    valueIn >> value;
    AddValue(value);
}

void DocumentLineParser::UpdateDocument(Document &document) const
{
    if (m_valueType == Time)
        document.AddTimes(m_values);
    else
        document.AddDistances(m_values);
}

DocumentParser::DocumentParser(Document &document, const bool parseAsOneRace) : 
    FileParser(std::unique_ptr<LineParserFactoryBase>(parseAsOneRace ? static_cast<LineParserFactoryBase *>(new LineParserFactory<Part2LineParser>) : static_cast<LineParserFactoryBase *>(new LineParserFactory<Part1LineParser>))),
    m_document(document)
{
}

void DocumentParser::OnEndLine(LineParser &lineParser)
{
    dynamic_cast<DocumentLineParser &>(lineParser).UpdateDocument(m_document);
}