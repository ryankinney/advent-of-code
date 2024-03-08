#include <gtest/gtest.h>
#include "DocumentParser.h"

TEST(TestCase, Test)
{
    Document document;
    DocumentParser parser(document);
    parser.Load("example.txt");
    EXPECT_EQ(document.CalculateMarginOfError(), 288);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}