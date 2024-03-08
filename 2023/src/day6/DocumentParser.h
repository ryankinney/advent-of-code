#pragma once

#include "Document.h"
#include "FileParser.h"

enum ValueType
{
    Time,
    Distance
};

class DocumentLineParser : public LineParser
{
public:
    DocumentLineParser(const bool parseAsOneRace) : m_parseAsOneRace(parseAsOneRace) {}

    void ParseLine(const std::string &line) override;

    void UpdateDocument(Document &document) const;

private:
    const bool m_parseAsOneRace;
    ValueType m_valueType = Time;
    std::vector<size_t> m_values;
};

class DocumentLineParserFactory : public LineParserFactoryBase
{
public:
    DocumentLineParserFactory(const bool parseAsOneRace) : m_parseAsOneRace(parseAsOneRace) {}

    std::unique_ptr<LineParser> CreateLineParser() override { return std::unique_ptr<LineParser>(new DocumentLineParser(m_parseAsOneRace)); }

private:
    const bool m_parseAsOneRace;
};

class DocumentParser : public FileParser
{
public:
    DocumentParser(Document &document, const bool parseAsOneRace);

protected:
    void OnEndLine(LineParser &lineParser) override;

private:
    const bool m_parseAsOneRace;
    Document &m_document;
};