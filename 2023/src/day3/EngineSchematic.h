#pragma once

#include "FileParser.h"
#include "StarTable.h"

class Item
{
public:
    void MarkAsNumber(const size_t numberIndex) { m_isNumber = true; m_numberIndex = numberIndex; }

    bool IsNumber() const { return m_isNumber; }
    size_t GetNumberIndex() const { return m_numberIndex; }

private:
    bool m_isNumber = false;
    size_t m_numberIndex = 0;
};

class Row : public LineParser
{
public:
    void Init(NumberTable &numbersTable, StarTable &starTable) { m_numberTable = &numbersTable; m_starTable = &starTable; }
    void ParseLine(const std::string &line) override;

    size_t Size() const { return m_items.size(); }
    const Item &Get(const size_t index) const { return m_items[index]; }

private:
    NumberTable *m_numberTable = nullptr;
    StarTable *m_starTable = nullptr;
    std::vector<Item> m_items;
};

class EngineSchematic : public FileParser
{
public:
    EngineSchematic() : FileParser(std::unique_ptr<LineParserFactoryBase>(new LineParserFactory<Row>)) {}

    void FindPartNumbersAndGears();
    size_t CalculateSumOfPartNumbers() const { return m_numberTable.CalculateSumOfPartNumbers(); }
    size_t CalculateSumOfGearRatios() const { return m_starTable.CalculateSumOfGearRatios(m_numberTable); }

protected:
    size_t GetNumRows() const { return GetLineParsers().size(); }
    const Row &GetRow(const size_t index) const { return dynamic_cast<const Row &>(*GetLineParsers()[index]); }

    virtual void OnBeginLine(LineParser &lineParser) override { dynamic_cast<Row &>(lineParser).Init(m_numberTable, m_starTable); }
    virtual void OnEndLine(LineParser &lineParser) override { m_starTable.AdvanceRow(); }

private:
    void CheckAdjacentItem(const size_t rowIndex, const size_t itemIndex, StarInfo &symbol);

    NumberTable m_numberTable;
    StarTable m_starTable;
};