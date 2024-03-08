#include <gtest/gtest.h>
#include "DocumentParser.h"

TEST(Document, Part1Example)
{
    Document document;
    DocumentParser parser(document, false);
    parser.Load("example.txt");
    EXPECT_EQ(document.CalculateMarginOfError(), 288);
}

TEST(Document, Part2Example)
{
    Document document;
    DocumentParser parser(document, true);
    parser.Load("example.txt");
    EXPECT_EQ(document.CalculateMarginOfError(), 71503);
}

TEST(Document, Part1Input)
{
    Document document;
    DocumentParser parser(document, false);
    parser.Load("input.txt");
    EXPECT_EQ(document.CalculateMarginOfError(), 140220);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}