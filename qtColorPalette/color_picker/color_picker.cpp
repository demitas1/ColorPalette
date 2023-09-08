#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QLinearGradient>
#include <QConicalGradient>
#include <QtMath>
#include <QDebug>

#include "color_picker.h"
#include "ui_color_picker.h"


const float PI = 3.14159;


QRectF shrinkRect(QRectF r, float t) {
    const float x = r.x();
    const float y = r.y();
    const float w = r.width();
    const float h = r.height();
    return QRectF(
        x + w / 2 * (1.0 - t),
        y + h / 2 * (1.0 - t),
        w * t,
        h * t);
}


QPointF pointPolar(float radius, float rad) {
    return QPointF(radius * qCos(rad), radius * qSin(rad));
}


// TODO: test this
std::pair<float, float> decompose(QPointF p, QPolygonF triangle) {
    if (triangle.length() < 3) {
        return std::make_pair<float, float>(NAN, NAN);
    }

    QPointF v0 = triangle[0];
    QPointF v1 = triangle[1];
    QPointF v2 = triangle[2];

    // Bases of two edges of triangle
    float x1 = v1.x() - v0.x();
    float y1 = v1.y() - v0.y();
    float x2 = v2.x() - v0.x();
    float y2 = v2.y() - v0.y();

    // Vector to decompose
    float x = p.x() - v0.x();
    float y = p.y() - v0.y();

    float denom = x1 * y2 - x2 * y1;
    if (std::fabs(denom) < 1e-9) {
        return std::make_pair<float, float>(NAN, NAN);
    }

    float s = (y2 * x - x2 * y) / denom;
    float t = (y * x1 - x * y1) / denom;
    return std::make_pair(s, t);
}


bool inTriangle(float s, float t) {
    return
        0.0 <= s && s <= 1.0 &&
        0.0 <= t && t <= 1.0 &&
        0.0 <= (s + t) && (s + t) <= 1.0;
}


ColorPicker::ColorPicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPicker)
{
    ui -> setupUi(this);
    setColor(QColor(Qt::red));
}

ColorPicker::~ColorPicker()
{
    delete ui;
}

void ColorPicker::setColor(QColor c)
{
    _color = c;
    _colorHue = _color.hsvHueF();
    _colorSat = _color.hsvSaturationF();
    _colorVal = _color.valueF();

    update();
}

void ColorPicker::mousePressEvent(QMouseEvent *event)
{

}

void ColorPicker::mouseReleaseEvent(QMouseEvent *event)
{

}

void ColorPicker::mouseMoveEvent(QMouseEvent *event)
{

}

void ColorPicker::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor colorBack = QColor(48, 48, 48, 255);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(colorBack));
    painter.setBrush(colorBack);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawRect(rect());

    // draw color hue ring
    // TODO: consider resize. keep aspect ration = 1.0
    float radiusRatio = 0.7;
    float radiusOuter = rect().width() / 2;
    float radiusInner = rect().width() / 2 * radiusRatio;

    QConicalGradient gradRing(rect().center(), 0);
    gradRing.setColorAt(0.0,    Qt::red);
    gradRing.setColorAt(0.1667, Qt::yellow);
    gradRing.setColorAt(0.3333, Qt::green);
    gradRing.setColorAt(0.5,    Qt::cyan);
    gradRing.setColorAt(0.6667, Qt::blue);
    gradRing.setColorAt(0.8333, Qt::magenta);
    gradRing.setColorAt(1.0,    Qt::red);

    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(gradRing);
    painter.drawPie(rect(), 0 * 16, 360 * 16);
    painter.setBrush(colorBack);
    painter.drawPie(shrinkRect(rect(), radiusRatio), 0 * 16, 360 * 16);

    // draw current color hue position
    float radHue = _colorHue * 2 * PI;
    QPointF pHueOuter = rect().center() + pointPolar(radiusOuter, radHue);
    QPointF pHueInner = rect().center() + pointPolar(radiusInner, radHue);
    painter.setPen(QPen(QBrush(Qt::white), 2));
    painter.setBrush(Qt::white);
    painter.drawLine(pHueInner, pHueOuter);

    // sat/val triangle
    QPointF v0 = pHueInner;
    QPointF v1 = rect().center() + pointPolar(radiusInner, radHue + PI * 2 / 3);
    QPointF v2 = rect().center() + pointPolar(radiusInner, radHue + PI * 4 / 3);

    // draw sat/val triangle edges
    // NOTE: every point on v1~v2 edge is chroma-zero gray
    QLinearGradient gradEdge01 = QLinearGradient(v0, v1);
    QLinearGradient gradEdge02 = QLinearGradient(v0, v2);
    QLinearGradient gradEdge12 = QLinearGradient(v1, v2);
    QColor c0, c12;
    c0.setHsvF(_colorHue, 1.0, 1.0);
    c12.setHsvF(_colorHue, 0.5, 0.5);
    gradEdge01.setColorAt(0.0, c0);
    gradEdge01.setColorAt(1.0, Qt::white);
    gradEdge02.setColorAt(0.0, c0);
    gradEdge02.setColorAt(1.0, Qt::black);
    gradEdge12.setColorAt(0.0, Qt::white);
    gradEdge12.setColorAt(1.0, Qt::black);
    painter.setPen(QPen(gradEdge01, 2));
    painter.setBrush(gradEdge01);
    painter.drawLine(v0, v1);
    painter.setPen(QPen(gradEdge02, 2));
    painter.setBrush(gradEdge02);
    painter.drawLine(v0, v2);
    painter.setPen(QPen(gradEdge12, 2));
    painter.setBrush(gradEdge12);
    painter.drawLine(v1, v2);

    // fill sat/val triangle
    QPolygonF triangle;
    triangle << v0 << v1 << v2;
    QRectF bbTriangle = triangle.boundingRect();
    const int bbLeft = qFloor(bbTriangle.left());
    const int bbTop = qFloor(bbTriangle.top());
    const int bbRight = qCeil(bbTriangle.right());
    const int bbBottom = qCeil(bbTriangle.bottom());
    for (int y = bbTop; y < bbBottom; y++) {
        for (int x = bbLeft; x < bbRight; x++) {
            // TODO: use drawPoints with QList<QPointF>
            QColor c;
            const QPointF p = QPointF(x, y);
            const auto st = decompose(p, triangle);
            const float s = st.first;
            const float t = st.second;
            if (inTriangle(s, t)) {
                // make gradient
                float chroma = 1.0 - (s + t);
                float saturation;
                if (1 - t < 1e-9) {
                    saturation = 0.0;
                } else {
                    saturation = qMin(1.0, chroma / (1 - t));
                }
                c.setHsvF(_colorHue, saturation, 1 - t);
                painter.setPen(c);
                painter.drawPoint(p);
            }
        }
    }

    // draw point of current color
    float s, t;
    if (_colorVal < 1e-9) {
        t = 1.0;
        s = 0.0;
    } else {
        t = 1.0 - _colorVal;
        s = _colorVal * (1.0 - _colorSat);
    }
    QPointF vc = v0 + t * (v2 - v0) +  s * (v1 - v0);
    painter.setPen(QPen(QBrush(Qt::white), 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(vc, 5, 5);
}
