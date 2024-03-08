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

    size_t value = 0;
    while (in >> value)
        m_values.push_back(value);
}

void DocumentLineParser::UpdateDocument(Document &document) const
{
    if (m_valueType == Time)
        document.AddTimes(m_values);
    else
        document.AddDistances(m_values);
}

DocumentParser::DocumentParser(Document &document) : 
    FileParser(std::unique_ptr<LineParserFactoryBase>(new LineParserFactory<DocumentLineParser>)),
    m_document(document)
{
}

void DocumentParser::OnEndLine(LineParser &lineParser)
{
    dynamic_cast<DocumentLineParser &>(lineParser).UpdateDocument(m_document);
}