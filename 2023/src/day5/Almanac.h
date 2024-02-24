#pragma once

#include <string>
#include <vector>

class Range
{
public:
    Range(const size_t start, const size_t size) : m_start(start), m_size(size) {}

    void Reset(const size_t start, const size_t size) { m_start = start; m_size = size; }

    size_t GetStart() const { return m_start; }
    size_t GetSize() const { return m_size; }

private:
    size_t m_start;
    size_t m_size;
};
typedef std::vector<Range> Ranges;

class RangeMapEntry
{
public:
    RangeMapEntry(const size_t destinationStart, const size_t sourceStart, const size_t length);

    void Print() const;
    std::pair<bool, size_t> MapValue(const size_t sourceValue) const;

private:
    size_t m_destinationStart = 0;
    size_t m_sourceStart = 0;
    size_t m_length;
};
typedef std::vector<RangeMapEntry> RangeMapEntries;

class RangeMap
{
public:
    RangeMap(const std::string &sourceCategory, const std::string &destinationCategory) :
        m_sourceCategory(sourceCategory), m_destinationCategory(destinationCategory)
    {
    }

    const std::string &GetSourceCategory() const { return m_sourceCategory; }
    const std::string &GetDestinationCategory() const { return m_destinationCategory; }
    void Print() const;

    void AddRange(const size_t destinationStart, const size_t sourceStart, const size_t length) { m_entries.push_back(RangeMapEntry(destinationStart, sourceStart, length)); }
    size_t MapValue(const size_t source) const;

private:
    std::string m_sourceCategory;
    std::string m_destinationCategory;
    RangeMapEntries m_entries;
};
typedef std::vector<RangeMap> RangeMaps;

class Almanac
{
public:
    void AddSeed(const size_t seed) { m_seeds.push_back(Range(seed, 1)); }
    void AddRangeMap(const std::string &sourceCategory, const std::string &destinationCategory) { m_rangeMaps.push_back(RangeMap(sourceCategory, destinationCategory)); }
    void AddRange(const size_t destinationStart, const size_t sourceStart, const size_t length) { m_rangeMaps.back().AddRange(destinationStart, sourceStart, length); }

    void PrintSeeds() const;
    void PrintRangeMaps() const;
    RangeMaps::const_iterator FindRangeMap(const std::string &sourceCategory) const;
    void CopySeeds(Ranges &seeds) const { seeds = m_seeds; }
    size_t CalculateMinLocation() const;

private:
    Ranges m_seeds;
    RangeMaps m_rangeMaps;
};