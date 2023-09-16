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
    QPixmap	_pix;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MY_CANVAS_H
