#include <gtest/gtest.h>
#include "AlmanacParser.h"

TEST(Almanac, Example)
{
    Almanac almanac;
    AlmanacFileParser(almanac).Load("example.txt");

    typedef std::vector<size_t> Locations;
    Locations locations;
    almanac.CopySeeds(locations);

    std::string sourceCategory = "seed";
    while (sourceCategory != "location")
    {
        RangeMaps::const_iterator rangeMap = almanac.FindRangeMap(sourceCategory);
        for (Locations::iterator iter = locations.begin(); iter != locations.end(); iter++)
            *iter = rangeMap->MapValue(*iter);

        std::cout << rangeMap->GetDestinationCategory() << ": ";
        for (Locations::const_iterator iter = locations.begin(); iter != locations.end(); iter++)
            std::cout << *iter << ' ';
        std::cout << std::endl;

        sourceCategory = rangeMap->GetDestinationCategory();
    }

    size_t minLocation = 0;
    if (!locations.empty())
        minLocation = locations[0];
    for (Locations::const_iterator iter = locations.begin(); iter != locations.end(); iter++)
        minLocation = std::min(minLocation, *iter);
    std::cout << minLocation << std::endl;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
