#pragma once

#include <set>
#include <string>
#include <vector>

class Engine
{
public:
    void Build(const std::string &filename);
    size_t AddPartNumbers() const;
    size_t AddGearRatios() const;

private:
    struct Num
    {
        std::string strValue;
        bool isPartNumber = false;
        size_t value;
    };
    typedef std::vector<Num> Numbers;

    struct MatrixElement
    {
        bool hasNumber = false;
        size_t numberIndex = 0;
    };
    typedef std::vector<std::vector<MatrixElement>> Matrix;

    struct Symbol
    {
        size_t x = 0;
        size_t y = 0;
        bool isAsterisk = false;
        std::set<size_t> adjacentParts;
    };
    typedef std::vector<Symbol> Symbols;

    void ParseLine(const size_t currentY, const std::string &line);
    void ParseFile(const std::string &filename);
    void CheckMatrixElement(const size_t x, const size_t y, Symbol &symbol);
    void FindPartNumbersAndGears();
    void ParseNumbers();

    Matrix matrix;
    Numbers numbers;
    Symbols symbols;
};