#ifndef MY_CANVAS_H
#define MY_CANVAS_H

#include <QWidget>

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
};

#endif // MY_CANVAS_H
