#include "Almanac.h"

#include <algorithm>
#include <iostream>

Range::Range(const size_t destinationStart, const size_t sourceStart, const size_t length) :
    m_destinationStart(destinationStart),
    m_sourceStart(sourceStart),
    m_length(length)
{
}

void Range::Print() const
{
    std::cout << m_destinationStart << ' ' << m_sourceStart << ' ' << m_length << std::endl;
}

std::pair<bool, size_t> Range::MapValue(const size_t sourceValue) const
{
    std::pair<bool, size_t> ret = std::make_pair(false, 0);
    if (sourceValue >= m_sourceStart && sourceValue < m_sourceStart + m_length)
        ret = std::make_pair(true, m_destinationStart + sourceValue - m_sourceStart);
    return ret;
}

void RangeMap::Print() const
{
    std::cout << m_sourceCategory << "-->" << m_destinationCategory << std::endl;
    for (Ranges::const_iterator iter = m_ranges.begin(); iter != m_ranges.end(); iter++)
        iter->Print();
}

size_t RangeMap::MapValue(const size_t sourceValue) const
{
    std::pair<bool, size_t> ret = std::make_pair(false, 0);
    for (Ranges::const_iterator iter = m_ranges.begin(); iter != m_ranges.end(); iter++)
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
        std::cout << m_seeds[index] << ' ';
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
    typedef std::vector<size_t> Locations;
    Locations locations;
    CopySeeds(locations);

    std::string sourceCategory = "seed";
    while (sourceCategory != "location")
    {
        RangeMaps::const_iterator rangeMap = FindRangeMap(sourceCategory);
        for (Locations::iterator iter = locations.begin(); iter != locations.end(); iter++)
            *iter = rangeMap->MapValue(*iter);
        sourceCategory = rangeMap->GetDestinationCategory();
    }
    return *std::min_element(locations.begin(), locations.end());
}