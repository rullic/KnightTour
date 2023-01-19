#include "mainwindow.h"
#include "boardarea.h"
#include "knighttoursolver.h"
#include "solverthread.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mBoardArea = new BoardArea;
    mSolver = new KnightTourSolver();
    mSolverThread = new SolverThread(mSolver, this);

    initializeUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::startSolver()
{
    mBoardArea->clearBoard();
    mSolverThread->startSolver(
        mRowSpinBox->value(), mColSpinBox->value(),
        mMethodComboBox->itemData(mMethodComboBox->currentIndex()).toInt());

    mStartButton->setEnabled(false);
}

void MainWindow::solverFinished(bool completed, int totalStep)
{
    QString result = completed? "completed." : "not completed.";
    result += " Number of total step = " + QString::number(totalStep);

    QMessageBox::information(this, "Knight's Tour", "Tour was " + result);
    mStartButton->setEnabled(true);
}

void MainWindow::initializeUI()
{
    setCentralWidget(new QFrame(this));

    mMethodLabel = new QLabel(tr("Solver &Method:"));
    mRowLabel = new QLabel(tr("Starting &Row:"));
    mColLabel = new QLabel(tr("Starting &Column:"));

    mMethodComboBox = new QComboBox;
    mMethodComboBox->addItem(tr("Backtracking"), KnightTourSolver::Backtracking);
    mMethodComboBox->addItem(tr("Heuristic"), KnightTourSolver::Heuristic);
    mMethodLabel->setBuddy(mMethodComboBox);

    mRowSpinBox = new QSpinBox;
    mColSpinBox = new QSpinBox;
    mRowSpinBox->setRange(0, 7);
    mColSpinBox->setRange(0, 7);

    mRowLabel->setBuddy(mRowSpinBox);
    mColLabel->setBuddy(mColSpinBox);

    mStartButton = new QPushButton(tr("Start Solving"));

    QGridLayout *mainLayout = new QGridLayout(this->centralWidget());
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);

    mainLayout->addWidget(mBoardArea, 0, 0, 1, 4);
    mainLayout->addWidget(mRowLabel, 1, 1);
    mainLayout->addWidget(mRowSpinBox, 1, 2);
    mainLayout->addWidget(mColLabel, 2, 1);
    mainLayout->addWidget(mColSpinBox, 2, 2);
    mainLayout->addWidget(mMethodLabel, 3, 1);
    mainLayout->addWidget(mMethodComboBox, 3, 2);
    mainLayout->addWidget(mStartButton, 4, 1, 1, 2);

    this->centralWidget()->setLayout(mainLayout);
    setWindowTitle(tr("Knight's Tour Problem"));

    connect(mStartButton, &QPushButton::clicked, this, &MainWindow::startSolver);
    connect(mSolver, &KnightTourSolver::moveTo, mBoardArea, &BoardArea::putNumber);
    connect(mSolver, &KnightTourSolver::solverFinished, this, &MainWindow::solverFinished);

    mBoardArea->update();
}

