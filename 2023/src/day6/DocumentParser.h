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
    void ParseLine(const std::string &line) override;

    void UpdateDocument(Document &document) const;

private:
    ValueType m_valueType = Time;
    std::vector<size_t> m_values;
};

class DocumentParser : public FileParser
{
public:
    DocumentParser(Document &document);

protected:
    void OnEndLine(LineParser &lineParser) override;

private:
    Document &m_document;
};