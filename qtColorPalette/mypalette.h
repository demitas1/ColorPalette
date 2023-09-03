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
    QRect mSwatch;
    QList<QColor> mColor;

public:
    explicit MyPalette(QWidget *parent = nullptr);
    void loadDefaultColors(void);

signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    // QWidget interface
public:
    QSize sizeHint() const override;

};

#endif // MYPALETTE_H
