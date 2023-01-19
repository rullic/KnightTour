#ifndef SOLVERTHREAD_H
#define SOLVERTHREAD_H

#include <QThread>

class KnightTourSolver;

class SolverThread : public QThread
{
    Q_OBJECT
public:
    explicit SolverThread(KnightTourSolver *solver, QObject *parent = nullptr);
    void startSolver(int startRow, int startCol, int method);

protected:
    void run() override;

private:
    KnightTourSolver *mSolver;
    int mStartRow = 0;
    int mStartCol = 0;
    int mMethod = 0;
};

#endif // SOLVERTHREAD_H
