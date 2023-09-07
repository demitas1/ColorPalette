#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <QWidget>

namespace Ui {
class ColorPicker;
}

class ColorPicker : public QWidget
{
    Q_OBJECT

private:
    Ui::ColorPicker *ui;
    QColor _color;
    float _colorHue;
    float _colorSat;
    float _colorVal;

public:
    explicit ColorPicker(QWidget *parent = nullptr);
    ~ColorPicker();

    // getter
    QColor color()   const { return _color; };
    float colorHue() const { return _colorHue; };
    float colorSat() const { return _colorSat; };
    float colorVal() const { return _colorVal; };

    void setColor(QColor c);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // COLOR_PICKER_H
