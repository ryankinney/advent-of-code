#include "part-numbers.h"

#include <fstream>
#include <sstream>
#include <vector>

namespace
{
    struct Num
    {
        std::string value;
        bool isPartNumber = false;
    };

    struct MatrixElement
    {
        bool hasNumber = false;
        size_t numberIndex = 0;
    };

    struct Loc
    {
        size_t x = 0;
        size_t y = 0;
    };

    typedef std::vector<Num> Numbers;
    typedef std::vector<std::vector<MatrixElement>> Matrix;
    typedef std::vector<Loc> SymbolLocs;

    void ParseLine(const size_t currentY, const std::string &line, Numbers &numbers, Matrix &matrix, SymbolLocs &symbolLocs)
    {
        std::string currentNumber;
        matrix.push_back(std::vector<MatrixElement>(line.size()));
        for (size_t currentX = 0; currentX < line.size(); currentX++)
        {
            const char currentChar = line[currentX];
            MatrixElement &currentMatrixElement = matrix[currentY][currentX];
            if (std::isdigit(currentChar))
            {
                currentNumber += currentChar;
                currentMatrixElement.hasNumber = true;
                currentMatrixElement.numberIndex = numbers.size();
            }
            else
            {              
                if (!currentNumber.empty())
                {
                    numbers.push_back(Num{currentNumber});
                    currentNumber.resize(0);               
                }

                currentMatrixElement.hasNumber = false;
                if (currentChar != '.')
                    symbolLocs.push_back(Loc{currentX, currentY});
            }
        }
        if (!currentNumber.empty())
            numbers.push_back(Num{currentNumber});
    }

    void ParseFile(const std::string &filename, Numbers &numbers, Matrix &matrix, SymbolLocs &symbolLocs)
    {
        std::string line;
        size_t currentY = 0;
        std::ifstream in(filename);
        while (std::getline(in, line))
        {
            ParseLine(currentY, line, numbers, matrix, symbolLocs);
            currentY++;
        }
    }

    void CheckMatrixElement(const Matrix &matrix, const size_t x, const size_t y, Numbers &numbers)
    {
        const MatrixElement &matrixElement = matrix[y][x];
        if (matrixElement.hasNumber)
            numbers[matrixElement.numberIndex].isPartNumber = true;
    }

    void MarkPartNumbers(const SymbolLocs &symbolLocs, const Matrix &matrix, Numbers &numbers)
    {
        for (const Loc &loc : symbolLocs)
        {
            const bool hasLeftOf = loc.x > 0;
            const bool hasAbove = loc.y > 0;
            const bool hasRightOf = loc.x < matrix[0].size() - 1;
            const bool hasBelow = loc.y < matrix.size() - 1;

            // Check for numbers in the row above the symbol
            if (hasAbove)
            {
                const size_t aboveY = loc.y - 1;
                if (hasLeftOf)
                    CheckMatrixElement(matrix, loc.x - 1, aboveY, numbers);
                CheckMatrixElement(matrix, loc.x, aboveY, numbers);
                if (hasRightOf)
                    CheckMatrixElement(matrix, loc.x + 1, aboveY, numbers);
            }

            // Check for numbers in the same row as the symbol
            const size_t sameY = loc.y;
            if (hasLeftOf)
                CheckMatrixElement(matrix, loc.x - 1, sameY, numbers);
            if (hasRightOf)
                CheckMatrixElement(matrix, loc.x + 1, sameY, numbers);

            // Check for number in the row below the symbol
            if (hasBelow)
            {
                const size_t belowY = loc.y + 1;
                if (hasLeftOf)
                    CheckMatrixElement(matrix, loc.x - 1, belowY, numbers);
                CheckMatrixElement(matrix, loc.x, belowY, numbers);
                if (hasRightOf)
                    CheckMatrixElement(matrix, loc.x + 1, belowY, numbers);
            }
        }
    }
}

size_t AddPartNumbers(const std::string &filename)
{
    Matrix matrix;
    Numbers numbers;
    SymbolLocs symbolLocs;
    ParseFile(filename, numbers, matrix, symbolLocs);
    MarkPartNumbers(symbolLocs, matrix, numbers);

    size_t sum = 0;
    for (const Num &number : numbers)
    {
        if (number.isPartNumber)
        {
            size_t value = 0;
            std::istringstream in(number.value);
            in >> value;
            sum += value; 
        }
    }
    return sum;
}