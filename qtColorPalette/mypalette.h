#ifndef MYPALETTE_H
#define MYPALETTE_H

#include <QWidget>

class MyPalette : public QWidget
{
    Q_OBJECT
public:
    explicit MyPalette(QWidget *parent = nullptr);

signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

    // QWidget interface
public:
    QSize sizeHint() const override;
};

#endif // MYPALETTE_H
