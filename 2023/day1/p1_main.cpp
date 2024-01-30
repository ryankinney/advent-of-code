#include <iostream>
#include "calibration.h"

int main()
{
    int sum = 0;
    std::string input;
    while (std::getline(std::cin, input))
    {
        const int calibrationValue = GetP1CalibrationValue(input);
        if (__builtin_sadd_overflow(sum, calibrationValue, &sum))
        {
            std::cerr << "ERROR: Overflow" << std::endl;
            exit(-1);
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
