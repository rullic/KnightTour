#include "boardarea.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

BoardArea::BoardArea(QWidget *parent)
    : QWidget{parent},
      mPen(QColor(Qt::black), 1),
      mBrush(QColor(Qt::white))
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    updateGeometry();
}

QSize BoardArea::sizeHint() const
{
    return QSize(BOARD_LENGTH + 20, BOARD_LENGTH + 20);
}

QSize BoardArea::minimumSizeHint() const
{
    return QSize(BOARD_LENGTH + 20, BOARD_LENGTH + 20);
}

void BoardArea::putNumber(int row, int col, int aNumber)
{
    mNumbers[row][col] = aNumber;
    update();
}

void BoardArea::clearBoard()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            mNumbers[i][j] = 0;
        }
    }
    update();
}

bool BoardArea::checkAllZero()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (mNumbers[i][j] != 0) return false;
        }
    }

    return true;
}

void BoardArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setPen(mPen);
    painter.setBrush(mBrush);

    QRect rect(10, 10, BOARD_LENGTH, BOARD_LENGTH);
    painter.drawRect(rect);

    for (auto x = 10; x < BOARD_LENGTH; x += BOX_LENGTH) {
        painter.drawLine(x, 10, x, 10 + BOARD_LENGTH);
    }

    for (auto y = 10; y < BOARD_LENGTH; y += BOX_LENGTH) {
        painter.drawLine(10, y, BOARD_LENGTH + 10, y);
    }

    painter.setFont(QFont("Arial", 14, QFont::Bold));
    for (auto i = 0; i < 8; i++) {
        for (auto j = 0; j < 8; j++) {
            if (mNumbers[i][j] != 0) {
                QRectF box(j * BOX_LENGTH + 10, i * BOX_LENGTH + 10,
                           BOX_LENGTH, BOX_LENGTH);
                painter.drawText(box, Qt::AlignCenter, QString::number(mNumbers[i][j]));
            }
        }
    }

}
