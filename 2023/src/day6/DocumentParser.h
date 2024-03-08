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

protected:
    void AddValue(const size_t value) { m_values.push_back(value); }
    virtual void ParseValues(std::istream &in) = 0;

private:
    ValueType m_valueType = Time;
    std::vector<size_t> m_values;
};

class Part1LineParser : public DocumentLineParser
{
protected:
    void ParseValues(std::istream &in) override;
};

class Part2LineParser : public DocumentLineParser
{
protected:
    void ParseValues(std::istream &in) override;
};

class DocumentParser : public FileParser
{
public:
    DocumentParser(Document &document, const bool parseAsOneRace);

protected:
    void OnEndLine(LineParser &lineParser) override;

private:
    Document &m_document;
};