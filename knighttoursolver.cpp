#include "knighttoursolver.h"
#include <QDebug>
#include <climits>

KnightTourSolver::KnightTourSolver()
{

}

void KnightTourSolver::start(int startRow, int startCol, int method)
{
    mNumStep = 0;
    mTotalStep = 0;
    clearBoard();

    if (KnightTourSolver::Method(method) == KnightTourSolver::Backtracking) {
        tryMove(startRow, startCol);
    } else {
        tryMoveWithHeuristic(startRow, startCol);
    }

    emit solverFinished(allBlocksVisited(), mTotalStep);

    qDebug() << "Total steps = " << mTotalStep;
}

void KnightTourSolver::clearBoard()
{
    std::array<int, 8> zeros{};
    mBoard.fill(zeros);
}

bool KnightTourSolver::tryMove(int curRow, int curCol)
{
    mBoard[curRow][curCol] = ++mNumStep;
    ++mTotalStep;
    emit moveTo(curRow, curCol, mNumStep);

    auto validMoves = generateValidMove(KnightPos(curRow, curCol));
    bool canMove = false;
    if (validMoves.empty()) {
        if (allBlocksVisited() || mTotalStep > 5000000) {
            return true;
        }
    } else {
        for (auto move : validMoves) {
            canMove = tryMove(move.row, move.column);
            if (canMove) break;
        }
    }

    if (!canMove) { // Backtracking
        mBoard[curRow][curCol] = 0;
        emit moveTo(curRow, curCol, 0);
        --mNumStep;
    }

    return canMove;
}

bool KnightTourSolver::tryMoveWithHeuristic(int curRow, int curCol)
{
    mBoard[curRow][curCol] = ++mNumStep;
    ++mTotalStep;
    emit moveTo(curRow, curCol, mNumStep);

    auto validMoves = generateValidMove(KnightPos(curRow, curCol));
    bool canMove = false;
    if (validMoves.empty()) {
        if (allBlocksVisited()) {
            return true;
        }
    } else if (validMoves.size() == 1) {
        canMove = tryMoveWithHeuristic(validMoves[0].row, validMoves[0].column);
    } else {
        KnightPos bestMove;
        auto minNumberOfValidMoves = UINT_MAX;
        for (auto move : validMoves) {
            auto nextValidMoves = generateValidMove(move);
            if (!nextValidMoves.empty() && nextValidMoves.size() < minNumberOfValidMoves) {
                bestMove = move;
                minNumberOfValidMoves = nextValidMoves.size();
            }
        }

        if (minNumberOfValidMoves < UINT_MAX) {
            canMove = tryMoveWithHeuristic(bestMove.row, bestMove.column);
        }
    }

    if (!canMove) {
        mBoard[curRow][curCol] = 0;
        emit moveTo(curRow, curCol, 0);
        --mNumStep;
    }

    if (mTotalStep > 5000000) return true;

    return canMove;
}

bool KnightTourSolver::allBlocksVisited()
{
    for (auto row = 0; row < 8; ++row) {
        for (auto col = 0; col < 8; ++ col) {
            if (mBoard[row][col] == 0) return false;
        }
    }

    return true;
}

std::vector<KnightPos> KnightTourSolver::generateValidMove(KnightPos startPos)
{
    std::vector<KnightPos> result;

    KnightPos nextPos;
    for (auto step : mAllSteps) {
        nextPos.column = startPos.column + std::get<0>(step);
        nextPos.row = startPos.row + std::get<1>(step);

        if (nextPos.column >= 0 && nextPos.column < 8 &&
            nextPos.row >= 0 && nextPos.row < 8 &&
            mBoard[nextPos.row][nextPos.column] == 0) {
            result.push_back(nextPos);
        }
    }

    return result;
}

