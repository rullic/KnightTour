#ifndef KNIGHTTOURSOLVER_H
#define KNIGHTTOURSOLVER_H

#include <array>

class KnightTourSolver
{
public:
    KnightTourSolver();
    bool solve(int startRow =0, int startCol = 0);

private:
    std::array<std::array<int, 8>, 8> mBoard{};

    void clearBoard();
};

#endif // KNIGHTTOURSOLVER_H
