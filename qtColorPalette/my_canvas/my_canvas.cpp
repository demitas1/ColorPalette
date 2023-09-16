#include <QPixmap>
#include <QPainter>
#include <QDebug>

#include "my_canvas.h"
#include "ui_my_canvas.h"

MyCanvas::MyCanvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyCanvas)
{
    ui -> setupUi(this);

    // initialize canvas pixmap
    _pix = QPixmap(100, 100);
}

MyCanvas::~MyCanvas()
{
    delete ui;
}

void MyCanvas::paintEvent(QPaintEvent *event)
{
    // show current pixmap
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawPixmap(0, 0, _pix);
}

void MyCanvas::mousePressEvent(QMouseEvent *event)
{
    // draw on pixmap
    QPainter painter(&_pix);
    painter.setPen(Qt::red);
    painter.drawPoint(0, 0);
    painter.drawPoint(1, 0);
    painter.drawPoint(1, 1);
    painter.drawPoint(0, 1);
    repaint();
}
