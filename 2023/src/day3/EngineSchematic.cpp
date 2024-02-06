#include "EngineSchematic.h"

#include <fstream>
#include <sstream>

void Row::ParseLine(const std::string &line)
{
    std::string currentNumber;
    m_items.resize(line.size());
    for (size_t currentX = 0; currentX < line.size(); currentX++)
    {
        const char currentChar = line[currentX];
        Item &currentItem = m_items[currentX];
        if (std::isdigit(currentChar))
        {
            currentNumber += currentChar;
            currentItem.MarkAsNumber(m_numberTable->GetNextIndex());
        }
        else
        {
            if (!currentNumber.empty())
            {
                m_numberTable->AddNumber(currentNumber);
                currentNumber.resize(0);
            }

            if (currentChar != '.')
            {
                m_starTable->AddStar(currentX);
            }
        }
    }
    if (!currentNumber.empty())
        m_numberTable->AddNumber(currentNumber);
}

void EngineSchematic::CheckAdjacentItem(const size_t rowIndex, const size_t itemIndex, StarInfo &star)
{
    const Item &item = GetRow(rowIndex).Get(itemIndex);
    if (item.IsNumber())
    {
        m_numberTable.MarkNumberAsPartNumber(item.GetNumberIndex());
        star.AddAdjacentPart(item.GetNumberIndex());
    }
}
void EngineSchematic::FindPartNumbersAndGears()
{
    for (size_t starIndex = 0; starIndex < m_starTable.Size(); starIndex++)
    {
        StarInfo &star = m_starTable.Get(starIndex);
        const size_t starRowIndex = star.GetRowIndex();
        const size_t starItemIndex = star.GetItemIndex();
        const bool hasItemToLeft = starItemIndex > 0;
        const bool hasRowAbove = starRowIndex > 0;
        const bool hasItemToRight = starItemIndex < GetRow(0).Size() - 1;
        const bool hasRowBelow = starRowIndex < GetNumRows() - 1;

        // Check for numbers in the row above the symbol
        if (hasRowAbove)
        {
            const size_t aboveRowIndex = starRowIndex - 1;
            if (hasItemToLeft)
                CheckAdjacentItem(aboveRowIndex, starItemIndex - 1, star);
            CheckAdjacentItem(aboveRowIndex, starItemIndex, star);
            if (hasItemToRight)
                CheckAdjacentItem(aboveRowIndex, starItemIndex + 1, star);
        }

        // Check for numbers in the same row as the symbol
        const size_t sameRowIndex = starRowIndex;
        if (hasItemToLeft)
            CheckAdjacentItem(sameRowIndex, starItemIndex - 1, star);
        if (hasItemToRight)
            CheckAdjacentItem(sameRowIndex, starItemIndex + 1, star);

        // Check for number in the row below the symbol
        if (hasRowBelow)
        {
            const size_t belowRowIndex = starRowIndex + 1;
            if (hasItemToLeft)
                CheckAdjacentItem(belowRowIndex, starItemIndex - 1, star);
            CheckAdjacentItem(belowRowIndex, starItemIndex, star);
            if (hasItemToRight)
                CheckAdjacentItem(belowRowIndex, starItemIndex + 1, star);
        }
    }
}