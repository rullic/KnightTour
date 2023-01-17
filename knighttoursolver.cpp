#include "knighttoursolver.h"

KnightTourSolver::KnightTourSolver()
{

}

bool KnightTourSolver::solve(int startRow, int startCol)
{
    clearBoard();

    return true;
}

void KnightTourSolver::clearBoard()
{
    std::array<int, 8> zeros{};
    mBoard.fill(zeros);
}
