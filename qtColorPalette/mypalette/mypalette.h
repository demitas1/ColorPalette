#ifndef MYPALETTE_H
#define MYPALETTE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QColor>


class MyPalette : public QWidget
{
    Q_OBJECT

private:
    // TODO: rename private members
    QRect _Swatch;
    QList<QColor> _Color;
    QColor _CurrentColor;
    QColor _CurrentBackgroundColor;

public:
    explicit MyPalette(QWidget *parent = nullptr);
    void loadDefaultColors(void);
    QColor currentColor(void);
    QColor currentBackgroundColor(void);

signals:
    void colorPicked();
    void backgroundColorPicked();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    // QWidget interface
public:
    QSize sizeHint() const override;

};

#endif // MYPALETTE_H
