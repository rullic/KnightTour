#ifndef BOARDAREA_H
#define BOARDAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>

class BoardArea : public QWidget
{
    Q_OBJECT
public:
    explicit BoardArea(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void clearBoard();

    bool checkAllZero();

public slots:
    void putNumber(int row, int col, int aNumber);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen mPen;
    QBrush mBrush;

    const int BOARD_LENGTH = 600;
    const int BOX_LENGTH = BOARD_LENGTH / 8;
    std::array<std::array<int, 8>, 8> mNumbers{};
};

#endif // BOARDAREA_H
