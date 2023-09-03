#include "mypalette.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>


MyPalette::MyPalette(QWidget *parent)
    : QWidget{parent}
{
    setSizePolicy(QSizePolicy(
        QSizePolicy::Preferred,
        QSizePolicy::Preferred));

    this -> mSwatch = QRect(0, 0, 30, 20);
    for (int i = 0; i < 80; i++) {
        this -> mColor << QColor(0, 0, 0);
    }
    this -> mCurrentColor = QColor(0, 0, 0);
}

void MyPalette::loadDefaultColors()
{
    qInfo() << "load default colors.";
    this -> mColor.clear();
    for (int i = 0; i < 80; i++) {
        const int r = int(255 * i / 80);
        this -> mColor << QColor(r, 255 - r, 255 - r);
    }
    this -> mCurrentColor = this -> mColor[0];
}

QColor MyPalette::currentColor()
{
    return this -> mCurrentColor;
}

void MyPalette::paintEvent(QPaintEvent *event)
{
    const int swW = this -> mSwatch.width();
    const int swH = this -> mSwatch.height();

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);

    QPainter painter(this);

    painter.setPen(pen);
    painter.setBrush(QColor(0, 0, 40));
    painter.drawRect(this -> rect());

    painter.setPen(pen);
    painter.setBrush(Qt::gray);
    painter.drawRect(QRectF(0, 0, 240, 200));

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 10; j++) {
            const QColor c = this -> mColor[i + j * 8];
            painter.setBrush(c);
            painter.drawRect(QRectF(swW * i, swH * j, swW, swH));
        }
    }
}

void MyPalette::mousePressEvent(QMouseEvent *ev)
{
    const int swW = this -> mSwatch.width();
    const int swH = this -> mSwatch.height();

    QPoint p = ev -> pos();
    const int i = int(p.x() / swW);
    const int j = int(p.y() / swH);

    const bool inBound = i < 8 || j < 10;
    const bool onBorder = (p.x() % swW == 0) || (p.y() % swH == 0);
    const int indexColor = i + j * 8;

    qInfo() << "mouse down: " << ev -> button()
            << " at " << i << "," << j;
    if (inBound && (! onBorder)) {
        QColor c = this -> mColor[indexColor];
        qInfo() << c;
        this -> mCurrentColor = c;

        emit colorPicked();
    }
}

QSize MyPalette::sizeHint() const
{
    return QSize(240, 200);
}
