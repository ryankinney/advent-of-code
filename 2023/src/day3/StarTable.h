#pragma once

#include <set>
#include "NumberTable.h"

class StarInfo
{
public:
    StarInfo(const std::size_t rowIndex, const std::size_t itemIndex) : m_rowIndex(rowIndex), m_itemIndex(itemIndex) {}

    std::size_t GetRowIndex() const { return m_rowIndex; }
    std::size_t GetItemIndex() const { return m_itemIndex; }
    std::size_t CalculateGearRatio(const NumberTable &numberTable) const;

    void AddAdjacentPart(const std::size_t numberIndex) { m_adjacentParts.insert(numberIndex); }

private:
    std::size_t m_rowIndex = 0;
    std::size_t m_itemIndex = 0;
    std::set<std::size_t> m_adjacentParts;
};

class StarTable
{
public:
    std::size_t Size() const { return m_stars.size(); }

    void AdvanceRow() { m_currentRow++; }
    void AddStar(const std::size_t itemIndex) { m_stars.push_back(StarInfo(m_currentRow, itemIndex)); }
    StarInfo &Get(const size_t index) { return m_stars[index]; }
    std::size_t CalculateSumOfGearRatios(const NumberTable &numberTable) const;

private:
    std::size_t m_currentRow = 0;
    std::vector<StarInfo> m_stars;
};