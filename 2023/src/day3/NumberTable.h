#pragma once

#include <string>
#include <vector>

class NumberTable
{
public:
    size_t GetNextIndex() const { return m_numbers.size(); }
    bool IsPartNumber(const size_t index) const { return m_numbers[index].isPartNumber; }
    size_t GetNumberValue(const size_t index) const { return m_numbers[index].value; }

    void AddNumber(const std::string &strValue);
    void MarkNumberAsPartNumber(const size_t index) { m_numbers[index].isPartNumber = true; }
    size_t CalculateSumOfPartNumbers() const;

private:
    struct NumberInfo
    {
        size_t value = 0;
        bool isPartNumber = false;
    };

    std::vector<NumberInfo> m_numbers;
};