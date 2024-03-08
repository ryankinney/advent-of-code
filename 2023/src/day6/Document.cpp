#include "Document.h"

#include <cmath>
#include <iostream>

size_t Document::CalculateMarginOfError() const
{
    size_t marginOfError = 1;
    for (size_t index = 0; index < m_times.size(); index++)
    {
        const double time = m_times[index];
        const double distance = m_distances[index];
        const double firstTerm = time/2;
        const double secondTerm = sqrt(time*time-4*distance)/-2;

        double lowerBound = firstTerm + secondTerm;
        if (lowerBound < 0)
        {
            lowerBound = 1;
        }
        else
        {
            double lowerBoundWholePart = 0;
            modf(lowerBound, &lowerBoundWholePart);
            lowerBound = lowerBoundWholePart + 1;
        }

        double upperBound = firstTerm - secondTerm, upperBoundWholePart = 0;
        if (modf(upperBound, &upperBoundWholePart) == 0)
            upperBound = upperBoundWholePart - 1;
        else
            upperBound = upperBoundWholePart;

        const size_t numberOfWaysToWin = static_cast<size_t>(upperBound - lowerBound + 1);
        marginOfError *= numberOfWaysToWin;
    }
    return marginOfError;
}