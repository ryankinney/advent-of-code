#include "Almanac.h"

#include <algorithm>
#include <iostream>

RangeMapEntry::RangeMapEntry(const size_t destinationStart, const size_t sourceStart, const size_t length) :
    m_destinationStart(destinationStart),
    m_sourceStart(sourceStart),
    m_length(length)
{
}

void RangeMapEntry::Print() const
{
    std::cout << m_destinationStart << ' ' << m_sourceStart << ' ' << m_length << std::endl;
}

std::pair<bool, size_t> RangeMapEntry::MapValue(const size_t sourceValue) const
{
    std::pair<bool, size_t> ret = std::make_pair(false, 0);
    if (sourceValue >= m_sourceStart && sourceValue < m_sourceStart + m_length)
        ret = std::make_pair(true, m_destinationStart + sourceValue - m_sourceStart);
    return ret;
}

void RangeMap::Print() const
{
    std::cout << m_sourceCategory << "-->" << m_destinationCategory << std::endl;
    for (RangeMapEntries::const_iterator iter = m_entries.begin(); iter != m_entries.end(); iter++)
        iter->Print();
}

size_t RangeMap::MapValue(const size_t sourceValue) const
{
    std::pair<bool, size_t> ret = std::make_pair(false, 0);
    for (RangeMapEntries::const_iterator iter = m_entries.begin(); iter != m_entries.end(); iter++)
    {
        ret = iter->MapValue(sourceValue);
        if (ret.first)
            break;
    }
    return ret.first ? ret.second : sourceValue;
}

void Almanac::PrintSeeds() const
{
    std::cout << "seeds: ";
    for (size_t index = 0; index < m_seeds.size(); index++)
        std::cout << m_seeds[index].GetStart() << ',' << m_seeds[index].GetSize() << ' ';
    std::cout << std::endl;
}

void Almanac::PrintRangeMaps() const
{
    std::for_each(m_rangeMaps.begin(), m_rangeMaps.end(), [](const RangeMap &rangeMap) { rangeMap.Print(); });
}

RangeMaps::const_iterator Almanac::FindRangeMap(const std::string &sourceCategory) const
{
    return std::find_if(m_rangeMaps.begin(), m_rangeMaps.end(), [sourceCategory](const RangeMap &rangeMap) { return rangeMap.GetSourceCategory() == sourceCategory; });
}

size_t Almanac::CalculateMinLocation() const
{
    Ranges locations;
    CopySeeds(locations);

    std::string sourceCategory = "seed";
    while (sourceCategory != "location")
    {
        RangeMaps::const_iterator rangeMap = FindRangeMap(sourceCategory);
        for (Ranges::iterator iter = locations.begin(); iter != locations.end(); iter++)
            iter->Reset(rangeMap->MapValue(iter->GetStart()), 1);
        sourceCategory = rangeMap->GetDestinationCategory();
    }
    return std::min_element(locations.begin(), locations.end(), [](const Range &range1, const Range &range2) { return range1.GetStart() < range2.GetStart(); })->GetStart();
}