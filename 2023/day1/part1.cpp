#include "part1.h"

#include <algorithm>
#include <cassert>
#include <fstream>

size_t P1::GetCalibrationValue(const std::string &input)
{
    size_t calibrationValue = 0;
    auto isDigit = [](char c) { return std::isdigit(c); };
    auto firstDigit = std::find_if(input.begin(), input.end(), isDigit);
    if (firstDigit != input.end())
    {
        auto lastDigit = std::find_if(input.rbegin(), input.rend(), isDigit);
        assert(lastDigit != input.rend()); // If a first digit was found, then a last digit should always be found too
        calibrationValue = 10*(*firstDigit - '0') + *lastDigit - '0';
    }
    return calibrationValue;
}

size_t P1::GetSum(const std::string &filename)
{
    size_t sum = 0;
    std::string line;
    std::ifstream in(filename);
    while (std::getline(in, line))
        sum += P1::GetCalibrationValue(line);
    return sum;
}