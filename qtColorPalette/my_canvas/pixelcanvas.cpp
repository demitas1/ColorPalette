#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QPixmap>
#include <QDebug>

#include "pixelcanvas.h"


PixelCanvas::PixelCanvas()
{
    _pix = new QPixmap(512, 512);

    setFlag(QGraphicsItem::ItemIsSelectable);
}

PixelCanvas::~PixelCanvas()
{
    delete _pix;
}

QRectF PixelCanvas::boundingRect() const
{
    return QRectF(0, 0, 512, 512);
}

void PixelCanvas::paint(
    QPainter *painter,
    const QStyleOptionGraphicsItem *option,
    QWidget *widget)
{
    painter -> drawPixmap(0, 0, *_pix);
}

void PixelCanvas::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    // draw on pixmap
    QPainter painter(_pix);
    QPointF p = ev -> pos();
    painter.setPen(Qt::red);
    painter.drawPoint(p);
    update();

    QGraphicsItem::mousePressEvent(ev);
}

void PixelCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    QGraphicsItem::mouseReleaseEvent(ev);
}
