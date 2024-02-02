#include "Engine.h"

#include <fstream>
#include <sstream>

void Engine::ParseLine(const size_t currentY, const std::string &line)
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
                symbols.push_back(Symbol{currentX, currentY, currentChar == '*'});
        }
    }
    if (!currentNumber.empty())
        numbers.push_back(Num{currentNumber});
}

void Engine::ParseFile(const std::string &filename)
{
    std::string line;
    size_t currentY = 0;
    std::ifstream in(filename);
    while (std::getline(in, line))
    {
        ParseLine(currentY, line);
        currentY++;
    }
}

void Engine::CheckMatrixElement(const size_t x, const size_t y, Symbol &symbol)
{
    const MatrixElement &matrixElement = matrix[y][x];
    if (matrixElement.hasNumber)
    {
        numbers[matrixElement.numberIndex].isPartNumber = true;
        symbol.adjacentParts.insert(matrixElement.numberIndex);
    }
}

void Engine::FindPartNumbersAndGears()
{
    for (Symbol &symbol : symbols)
    {
        const bool hasLeftOf = symbol.x > 0;
        const bool hasAbove = symbol.y > 0;
        const bool hasRightOf = symbol.x < matrix[0].size() - 1;
        const bool hasBelow = symbol.y < matrix.size() - 1;

        // Check for numbers in the row above the symbol
        if (hasAbove)
        {
            const size_t aboveY = symbol.y - 1;
            if (hasLeftOf)
                CheckMatrixElement(symbol.x - 1, aboveY, symbol);
            CheckMatrixElement(symbol.x, aboveY, symbol);
            if (hasRightOf)
                CheckMatrixElement(symbol.x + 1, aboveY, symbol);
        }

        // Check for numbers in the same row as the symbol
        const size_t sameY = symbol.y;
        if (hasLeftOf)
            CheckMatrixElement(symbol.x - 1, sameY, symbol);
        if (hasRightOf)
            CheckMatrixElement(symbol.x + 1, sameY, symbol);

        // Check for number in the row below the symbol
        if (hasBelow)
        {
            const size_t belowY = symbol.y + 1;
            if (hasLeftOf)
                CheckMatrixElement(symbol.x - 1, belowY, symbol);
            CheckMatrixElement(symbol.x, belowY, symbol);
            if (hasRightOf)
                CheckMatrixElement(symbol.x + 1, belowY, symbol);
        }
    }
}

void Engine::ParseNumbers()
{
    for (Num &number : numbers)
    {
        std::istringstream in(number.strValue);
        in >> number.value;
    }
}

void Engine::Build(const std::string &filename)
{
    ParseFile(filename);
    FindPartNumbersAndGears();
    ParseNumbers();
}

size_t Engine::AddPartNumbers() const
{
    size_t sum = 0;
    for (const Num &number : numbers)
        if (number.isPartNumber)
            sum += number.value; 
    return sum;
}

size_t Engine::AddGearRatios() const
{
    size_t sum = 0;
    for (const Symbol &symbol : symbols)
    {
        if (symbol.isAsterisk && symbol.adjacentParts.size() == 2)
        {
            std::set<size_t>::const_iterator iter = symbol.adjacentParts.begin();
            const size_t firstPartIndex = *iter++;
            const size_t secondPartIndex = *iter;
            sum += numbers[firstPartIndex].value * numbers[secondPartIndex].value;
        }
    }
    return sum;
}