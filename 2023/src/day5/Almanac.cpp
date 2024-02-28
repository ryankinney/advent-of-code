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

Range RangeMapEntry::MapRange(const Range &sourceRange, Range &leftRemainder, Range &rightRemainder) const
{
    Range overlap;
    const size_t overlapStart = std::max(m_sourceStart, sourceRange.GetStart());
    const size_t overlapStop = std::min(m_sourceStart + m_length, sourceRange.GetStart() + sourceRange.GetSize());
    if (overlapStart < overlapStop)
    {
        if (sourceRange.GetStart() < overlapStart)
            leftRemainder = Range(sourceRange.GetStart(), overlapStart - sourceRange.GetStart());
        overlap = Range(overlapStart, overlapStop - overlapStart);
        if (sourceRange.GetStart() + sourceRange.GetSize() > m_sourceStart + m_length)
        {
            rightRemainder = Range(overlapStop, sourceRange.GetSize() - overlapStop);
        }
    }

    Range mappedRange;
    if (!overlap.IsEmpty())
    {
        const size_t offsetInRange = overlap.GetStart() - m_sourceStart;
        mappedRange = Range(m_destinationStart + offsetInRange, overlap.GetSize());
    }
    return mappedRange;
}

void RangeMap::Print() const
{
    std::cout << m_sourceCategory << "-->" << m_destinationCategory << std::endl;
    for (RangeMapEntries::const_iterator iter = m_entries.begin(); iter != m_entries.end(); iter++)
        iter->Print();
}

void RangeMap::MapRange(const Range &originalSourceRange, Ranges &destinationRanges) const
{
    Ranges sourceRanges;
    sourceRanges.push_back(originalSourceRange);
    while (!sourceRanges.empty())
    {
        const Range &sourceRange = sourceRanges.back();
        sourceRanges.pop_back();

        Range destinationRange = sourceRange;
        for (RangeMapEntries::const_iterator iter = m_entries.begin(); iter != m_entries.end(); iter++)
        {
            Range leftRemainder, rightRemainder;
            const Range &mappedRange = iter->MapRange(sourceRange, leftRemainder, rightRemainder);
            if (!mappedRange.IsEmpty())
            {
                if (!leftRemainder.IsEmpty())
                    sourceRanges.push_back(leftRemainder);
                if (!rightRemainder.IsEmpty())
                    sourceRanges.push_back(rightRemainder);
                destinationRange = mappedRange;
                break;
            }
        }
        destinationRanges.push_back(destinationRange);
    }
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
        Ranges destinationRanges;
        RangeMaps::const_iterator rangeMap = FindRangeMap(sourceCategory);
        for (Ranges::iterator iter = locations.begin(); iter != locations.end(); iter++)
            rangeMap->MapRange(*iter, destinationRanges);

        sourceCategory = rangeMap->GetDestinationCategory();
        locations = destinationRanges;
    }
    return std::min_element(locations.begin(), locations.end(), [](const Range &range1, const Range &range2) { return range1.GetStart() < range2.GetStart(); })->GetStart();
}