#include <QPixmap>
#include <QPainter>
#include <QDebug>

#include "my_canvas.h"
#include "pixelcanvas.h"
#include "ui_my_canvas.h"


MyCanvas::MyCanvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyCanvas)
{
    ui -> setupUi(this);

    _scene = new QGraphicsScene(this);
    ui -> graphicsView -> setScene(_scene);
    ui -> graphicsView -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui -> graphicsView -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // create our object and add it to the scene
    _pixelCanvas = new PixelCanvas();
    _scene -> addItem(_pixelCanvas);
}

MyCanvas::~MyCanvas()
{
    delete _pixelCanvas;
    delete ui;
}

void MyCanvas::paintEvent(QPaintEvent *event)
{
}

void MyCanvas::mousePressEvent(QMouseEvent *event)
{
}
