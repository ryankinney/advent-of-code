#include "FileParser.h"

#include <fstream>

void FileParser::Load(const std::string &filename)
{
    std::string line;
    std::ifstream in(filename);
    while (std::getline(in, line))
    {
        std::unique_ptr<LineParser> lineParser = m_lineParserFactory->CreateLineParser();
        lineParser->ParseLine(line);
        m_lineParsers.push_back(std::move(lineParser));
    }
}