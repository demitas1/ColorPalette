#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QLinearGradient>
#include <QConicalGradient>
#include <QDebug>

#include "color_picker.h"
#include "ui_color_picker.h"


QRectF shrinkRect(QRectF r, float t) {
    const float x = r.x();
    const float y = r.y();
    const float w = r.width();
    const float h = r.height();
    return QRectF(
        x + w / 2 * (1.0 - t),
        y + h / 2 * (1.0 - t),
        w * t,
        h * t);
}


ColorPicker::ColorPicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPicker)
{
    ui -> setupUi(this);
}

ColorPicker::~ColorPicker()
{
    delete ui;
}

void ColorPicker::mousePressEvent(QMouseEvent *event)
{

}

void ColorPicker::mouseReleaseEvent(QMouseEvent *event)
{

}

void ColorPicker::mouseMoveEvent(QMouseEvent *event)
{

}

void ColorPicker::paintEvent(QPaintEvent *event)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);

    QPainter painter(this);

    painter.setPen(pen);
    painter.setBrush(Qt::gray);
    painter.drawRect(rect());

    // draw color hue ring
    QConicalGradient conicalGrad(rect().center(), 0);
    conicalGrad.setColorAt(0.0, Qt::red);
    conicalGrad.setColorAt(0.1667, Qt::yellow);
    conicalGrad.setColorAt(0.3333, Qt::green);
    conicalGrad.setColorAt(0.5, Qt::cyan);
    conicalGrad.setColorAt(0.6667, Qt::blue);
    conicalGrad.setColorAt(0.8333, Qt::magenta);
    conicalGrad.setColorAt(1.0, Qt::red);

    pen.setColor(Qt::transparent);
    painter.setPen(pen);
    painter.setBrush(conicalGrad);
    painter.drawPie(rect(), 0 * 16, 360 * 16);
    painter.setBrush(Qt::black);
    painter.drawPie(shrinkRect(rect(), 0.7), 0 * 16, 360 * 16);
}
