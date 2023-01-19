#ifndef KNIGHTTOURSOLVER_H
#define KNIGHTTOURSOLVER_H

#include <QObject>
#include <array>
#include <vector>
#include <tuple>

struct KnightPos {

    KnightPos(int r = -1, int c = -1) :
        row(r), column(c) {}

    int row;
    int column;
};

class KnightTourSolver : public QObject
{
    Q_OBJECT

public:
    enum Method { Backtracking, Heuristic };

    KnightTourSolver();
    void start(int startRow = 0, int startCol = 0, int method = 0);
    std::vector<KnightPos> generateValidMove(KnightPos startPos);
    bool allBlocksVisited();

signals:
    void moveTo(int row, int col, int stepNumber);
    void solverFinished(bool completed, int totalStep);

private:
    std::array<std::array<int, 8>, 8> mBoard{};
    using Step = std::tuple<int, int>;
    std::array<Step, 8> mAllSteps{
        Step(-2, -1), Step(-1, -2), Step(1, -2), Step(2, -1),
        Step(2, 1), Step(1, 2), Step(-1, 2), Step(-2, 1)
    };

    void clearBoard();
    bool tryMove(int curRow, int curCol);
    bool tryMoveWithHeuristic(int curRow, int curCol);

    int mNumStep = 0;
    int mTotalStep = 0;
};

#endif // KNIGHTTOURSOLVER_H
