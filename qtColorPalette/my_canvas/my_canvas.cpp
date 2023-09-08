#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>

#include "my_canvas.h"
#include "ui_my_canvas.h"

MyCanvas::MyCanvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyCanvas)
{
    ui -> setupUi(this);

    auto * scene = new QGraphicsScene(this);
    scene -> setSceneRect(-300, -300, 600, 600);
    scene -> setBackgroundBrush(QBrush(Qt::white));

    scene -> addLine(-300, 0, 300, 0);
    scene -> addLine(0, -300, 0, 300);

    auto * rect = scene -> addRect(10, 10, 100, 100);
    rect -> setFlag(QGraphicsItem::ItemIsSelectable);
    rect -> setFlag(QGraphicsItem::ItemIsMovable);

    auto * view = new QGraphicsView(this);
    view -> setAlignment(Qt::AlignTop | Qt:: AlignLeft);
    view -> setScene(scene);
}

MyCanvas::~MyCanvas()
{
    delete ui;
}
