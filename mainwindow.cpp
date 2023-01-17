#include "mainwindow.h"
#include <QtWidgets>
#include "boardarea.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mBoardArea = new BoardArea;
    setCentralWidget(new QFrame(this));

    mRowLabel = new QLabel(tr("Starting &Row:"));
    mColLabel = new QLabel(tr("Starting &Column:"));

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
    mainLayout->addWidget(mStartButton, 3, 1, 1, 2);
    // mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    this->centralWidget()->setLayout(mainLayout);
    setWindowTitle(tr("Knight's Tour Problem"));

    mBoardArea->putNumber(3, 3, 14);
    mBoardArea->putNumber(5, 7, 25);

    mBoardArea->update();
}

MainWindow::~MainWindow()
{
}

