#include <QColor>
#include <QDebug>

#include "current_color.h"
#include "ui_current_color.h"

CurrentColor::CurrentColor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentColor)
{
    ui->setupUi(this);
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
