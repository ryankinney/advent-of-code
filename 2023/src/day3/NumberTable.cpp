#include "NumberTable.h"

#include <sstream>

void NumberTable::AddNumber(const std::string &strValue)
{
    std::istringstream in(strValue);
    size_t value = 0;
    in >> value;
    m_numbers.push_back(NumberInfo{value});
}

size_t NumberTable::CalculateSumOfPartNumbers() const
{
    size_t sum = 0;
    for (const NumberInfo &number : m_numbers)
        if (number.isPartNumber)
            sum += number.value; 
    return sum;
}