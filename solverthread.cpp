#include "solverthread.h"
#include "knighttoursolver.h"

SolverThread::SolverThread(KnightTourSolver *solver, QObject *parent)
    : QThread{parent}
    , mSolver(solver)
{
}

void SolverThread::startSolver(int startRow, int startCol, int method)
{
    mStartRow = startRow;
    mStartCol = startCol;
    mMethod = method;
    start();
}

void SolverThread::run()
{
    mSolver->start(mStartRow, mStartCol, mMethod);
}

