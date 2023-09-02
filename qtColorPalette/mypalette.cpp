#include "mypalette.h"
#include <QPainter>
#include <QPen>
#include <QBrush>


MyPalette::MyPalette(QWidget *parent)
    : QWidget{parent}
{
    setSizePolicy(QSizePolicy(
        QSizePolicy::Preferred,
        QSizePolicy::Preferred));
}

void MyPalette::paintEvent(QPaintEvent *event)
{
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(Qt::gray);

    painter.drawRect(QRectF(0, 0, 300, 400));

}

QSize MyPalette::sizeHint() const
{
    return QSize(300, 400);
}
