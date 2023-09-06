#include <QColor>
#include <QDebug>

#include "current_color.h"
#include "ui_current_color.h"

CurrentColor::CurrentColor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentColor)
{
    ui -> setupUi(this);

    // arrange z-order
    ui -> backgroundColor -> stackUnder(ui -> foregroundColor);
}

CurrentColor::~CurrentColor()
{
    delete ui;
}

void CurrentColor::setForegroundColor(QColor c)
{
    qInfo() << "foreground color: " << c;
    ui -> foregroundColor -> setStyleSheet(
        QString("background-color: %1").arg(c.name()));
    ui -> foregroundColorName -> setText(c.name());
}

void CurrentColor::setBackgroundColor(QColor c)
{
    qInfo() << "foreground color: " << c;
    ui -> backgroundColor -> setStyleSheet(
        QString("background-color: %1").arg(c.name()));
}
