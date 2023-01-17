#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class BoardArea;

QT_BEGIN_NAMESPACE
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

private:
    BoardArea *mBoardArea;
    QLabel *mRowLabel;
    QLabel *mColLabel;
    QPushButton *mStartButton;
    QSpinBox *mRowSpinBox;
    QSpinBox *mColSpinBox;
};
#endif // MAINWINDOW_H
