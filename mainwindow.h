#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class BoardArea;
class KnightTourSolver;
class SolverThread;

QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QPushButton;
class QSpinBox;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startSolver();
    void solverFinished(bool completed, int totalStep);

private:
    KnightTourSolver *mSolver;
    SolverThread *mSolverThread;
    BoardArea *mBoardArea;

    QComboBox *mMethodComboBox;
    QLabel *mMethodLabel;
    QLabel *mRowLabel;
    QLabel *mColLabel;
    QPushButton *mStartButton;
    QSpinBox *mRowSpinBox;
    QSpinBox *mColSpinBox;

    void initializeUI();
};
#endif // MAINWINDOW_H
