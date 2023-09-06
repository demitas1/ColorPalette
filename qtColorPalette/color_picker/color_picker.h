#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <QWidget>

namespace Ui {
class ColorPicker;
}

class ColorPicker : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPicker(QWidget *parent = nullptr);
    ~ColorPicker();

private:
    Ui::ColorPicker *ui;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // COLOR_PICKER_H
