#include <gtest/gtest.h>
#include "Almanac.h"

TEST(Almanac, Example)
{
    Almanac almanac;
    almanac.Load("example.txt");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
