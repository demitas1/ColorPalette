#ifndef MY_CANVAS_H
#define MY_CANVAS_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "pixelcanvas.h"


namespace Ui {
class MyCanvas;
}

class MyCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit MyCanvas(QWidget *parent = nullptr);
    ~MyCanvas();

private:
    Ui::MyCanvas *ui;

    QGraphicsScene *_scene;
    PixelCanvas *_pixelCanvas;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MY_CANVAS_H
