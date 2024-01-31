#include "part2.h"

#include <array>
#include <fstream>
#include <vector>

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

size_t P2::GetCalibrationValue(const std::string &input)
{
    size_t calibrationValue = 0;
    int firstDigit = 0;
    if (FindDigit(frontwards, input.begin(), input.end(), &firstDigit))
    {
        int lastDigit = 0;
        FindDigit(backwards, input.rbegin(), input.rend(), &lastDigit);
        calibrationValue = 10*firstDigit + lastDigit;
    }
    return calibrationValue;
}

size_t P2::GetSum(const std::string &filename)
{
    size_t sum = 0;
    std::ifstream in(filename);
    std::string line;
    while (std::getline(in, line))
        sum += P2::GetCalibrationValue(line);
    return sum;
}