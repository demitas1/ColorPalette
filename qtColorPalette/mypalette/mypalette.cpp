#include "mypalette/mypalette.h"
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

    _Swatch = QRect(0, 0, 30, 20);
    for (int i = 0; i < 80; i++) {
        _Color << QColor(0, 0, 0);
    }
    _CurrentColor = QColor(0, 0, 0);
}

void MyPalette::loadDefaultColors()
{
    qInfo() << "load default colors.";
    _Color.clear();
    for (int i = 0; i < 80; i++) {
        const int r = int(255 * i / 80);
        _Color << QColor(r, 255 - r, 255 - r);
    }
    _CurrentColor = _Color[0];
}

QColor MyPalette::currentColor()
{
    return _CurrentColor;
}

QColor MyPalette::currentBackgroundColor()
{
    return _CurrentBackgroundColor;
}

void MyPalette::paintEvent(QPaintEvent *event)
{
    const int swW = _Swatch.width();
    const int swH = _Swatch.height();

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);

    QPainter painter(this);

    painter.setPen(pen);
    painter.setBrush(QColor(0, 0, 40));
    painter.drawRect(rect());

    painter.setPen(pen);
    painter.setBrush(Qt::gray);
    painter.drawRect(QRectF(0, 0, 240, 200));

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 10; j++) {
            const QColor c = _Color[i + j * 8];
            painter.setBrush(c);
            painter.drawRect(QRectF(swW * i, swH * j, swW, swH));
        }
    }
}

void MyPalette::mousePressEvent(QMouseEvent *ev)
{
    enum ColorTo {foreground, background};
    ColorTo colorTo;

    if (ev -> button() == Qt::LeftButton) {
        colorTo = foreground;
    } else if (ev -> button() == Qt::RightButton) {
        colorTo = background;
    } else {
        return;
    }

    const int swW = _Swatch.width();
    const int swH = _Swatch.height();

    QPoint p = ev -> pos();
    const int i = int(p.x() / swW);
    const int j = int(p.y() / swH);

    const bool inBound = i < 8 || j < 10;
    const bool onBorder = (p.x() % swW == 0) || (p.y() % swH == 0);
    const int indexColor = i + j * 8;

    qInfo() << "mouse down: " << ev -> button()
            << " at " << i << "," << j;
    if (inBound && (! onBorder)) {
        QColor c = _Color[indexColor];
        qInfo() << c;

        if (colorTo == foreground) {
            _CurrentColor = c;
            emit colorPicked();
        } else {
            _CurrentBackgroundColor = c;
            emit backgroundColorPicked();
        }
    }
}

QSize MyPalette::sizeHint() const
{
    return QSize(240, 200);
}
