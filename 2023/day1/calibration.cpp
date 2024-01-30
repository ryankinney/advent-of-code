#include "calibration.h"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace
{
    const static std::array<std::string, 10> frontwards
    {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };

    const static std::array<std::string, 10> backwards
    {
        "orez",
        "eno",
        "owt",
        "eerht",
        "ruof",
        "evif",
        "xis",
        "neves",
        "thgie",
        "enin"
    };

    template <class InputIt>
    bool FindDigit(const std::array<std::string, 10> &dictionary, InputIt first, InputIt last, int *digit)
    {
        bool foundDigit = false;
        *digit = 0;
        std::vector<int> allNumMatches(dictionary.size());
        for (auto iter = first; iter != last; iter++)
        {
            if (isdigit(*iter))
            {
                foundDigit = true;
                *digit = *iter - '0';
            }
            else
            {
                for (int index = 0; index < dictionary.size(); index++)
                {
                    const std::string &spelledOutDigit = dictionary[index];
                    int &numMatches = allNumMatches[index];
                    if (*iter == spelledOutDigit[numMatches])
                        numMatches++;
                    else if (*iter == spelledOutDigit[0])
                        numMatches = 1;
                    else
                        numMatches = 0;
                    if (numMatches == spelledOutDigit.size())
                    {
                       foundDigit = true;
                       *digit = index;
                       break;
                    }
                }
            }
            if (foundDigit)
                break;
        }
        return foundDigit;
    }
}

int GetP1CalibrationValue(const std::string &input)
{
    int calibrationValue = 0;
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

int GetP2CalibrationValue(const std::string &input)
{
    int calibrationValue = 0;
    int firstDigit = 0;
    if (FindDigit(frontwards, input.begin(), input.end(), &firstDigit))
    {
        int lastDigit = 0;
        const bool foundLastDigit = FindDigit(backwards, input.rbegin(), input.rend(), &lastDigit);
        assert(foundLastDigit); // If a first digit was found, then a last digit should always be found too
        calibrationValue = 10*firstDigit + lastDigit;
    }
    return calibrationValue;
}
