#pragma once

#include <memory>
#include <string>
#include <vector>

class LineParser
{
public:
    virtual ~LineParser() {}
    virtual void ParseLine(const std::string &line) = 0;
};

class LineParserFactoryBase
{
public:
    virtual ~LineParserFactoryBase() {}
    virtual std::unique_ptr<LineParser> CreateLineParser() = 0;
};

template <class T>
class LineParserFactory : public LineParserFactoryBase
{
public:
    std::unique_ptr<LineParser> CreateLineParser() override { return std::unique_ptr<LineParser>(new T); }
};

class FileParser
{
public:
    typedef std::vector<std::unique_ptr<LineParser>> LineParsers;

    FileParser(std::unique_ptr<LineParserFactoryBase> lineParserFactory) :
        m_lineParserFactory(std::move(lineParserFactory))
    {
    }

    void Load(const std::string &filename);

protected:
    const LineParsers &GetLineParsers() const { return m_lineParsers; }

    std::size_t GetNumLineParsers() const { return m_lineParsers.size(); }
    template <class T> T &GetLineParser(const size_t index) { return dynamic_cast<T &>(*m_lineParsers[index]); }
    template <class T> const T &GetLineParser(const size_t index) const { return dynamic_cast<const T &>(*m_lineParsers[index]); }

    virtual void OnBeginLine(LineParser &lineParser) {}
    virtual void OnEndLine(LineParser &lineParser) {}

    LineParsers m_lineParsers;

private:
    std::unique_ptr<LineParserFactoryBase> m_lineParserFactory;
};