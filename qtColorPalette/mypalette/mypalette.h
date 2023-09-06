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
    QColor mCurrentColor;
    QColor mCurrentBackgroundColor;

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
