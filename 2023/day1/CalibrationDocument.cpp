#include "CalibrationDocument.h"

#include <algorithm>
#include <fstream>

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
    bool FindDigit(const std::array<std::string, 10> &dictionary, InputIt first, InputIt last, size_t *digit)
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

void P1Calibration::ParseLine(const std::string &line)
{
    auto isDigit = [](char c) { return std::isdigit(c); };
    m_firstDigit = *std::find_if(line.begin(), line.end(), isDigit) - '0';
    m_lastDigit = *std::find_if(line.rbegin(), line.rend(), isDigit) - '0';
}

void P2Calibration::ParseLine(const std::string &line)
{
    FindDigit(frontwards, line.begin(), line.end(), &m_firstDigit);
    FindDigit(backwards, line.rbegin(), line.rend(), &m_lastDigit);  
}

size_t CalibrationDocument::GetSum() const
{
    size_t sum = 0;
    const LineParsers &lineParsers = GetLineParsers();
    for (LineParsers::const_iterator iter = lineParsers.begin(); iter != lineParsers.end(); iter++)
    {
        const Calibration &calibration = dynamic_cast<const Calibration &>(**iter);
        sum += calibration.GetValue();
    }
    return sum;
}