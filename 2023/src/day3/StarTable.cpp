#include "StarTable.h"

std::size_t StarInfo::CalculateGearRatio(const NumberTable &numberTable) const
{
    std::size_t gearRatio = 0;
    if (m_adjacentParts.size() == 2)
    {
        std::set<std::size_t>::const_iterator iter = m_adjacentParts.begin();
        const std::size_t firstPartIndex = *iter++;
        const std::size_t secondPartIndex = *iter;
        gearRatio = numberTable.GetNumberValue(firstPartIndex) * numberTable.GetNumberValue(secondPartIndex);
    }
    return gearRatio;
}

std::size_t StarTable::CalculateSumOfGearRatios(const NumberTable &numberTable) const
{
    std::size_t sum = 0;
    for (const StarInfo &star : m_stars)
        sum += star.CalculateGearRatio(numberTable);
    return sum;
}