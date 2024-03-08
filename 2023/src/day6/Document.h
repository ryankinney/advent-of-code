#pragma once

#include <vector>

class Document
{
public:
    typedef std::vector<std::size_t> Times;
    typedef std::vector<std::size_t> Distances;

    void AddTimes(const Times &times) { m_times = times; }
    void AddDistances(const Distances &distances) { m_distances = distances; }
    std::size_t CalculateMarginOfError() const;

private:
    Times m_times;
    Distances m_distances;
};