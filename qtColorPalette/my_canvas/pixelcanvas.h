#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <QPixmap>
#include <QGraphicsItem>

class PixelCanvas : public QGraphicsItem
{
protected:
    QPixmap * _pix;

public:
    explicit PixelCanvas();
    ~PixelCanvas();

public:
    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PIXELCANVAS_H
