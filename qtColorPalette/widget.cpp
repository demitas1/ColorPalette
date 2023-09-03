#include "widget.h"
#include "mypalette.h"
#include "./ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui -> currentColor -> setStyleSheet("background-color: #800000;");
    ui -> colorInfo -> setText("#800000");
    ui -> colorPalette -> loadDefaultColors();

    connect(
        ui -> colorPalette,
        &MyPalette::colorPicked,
        this,
        [=] () {
            this -> paletteColorPicked();
        });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paletteColorPicked()
{
    QColor c = ui -> colorPalette -> currentColor();
    qInfo() << "palette color is picked." << c.name();

    ui -> currentColor -> setStyleSheet(
        QString("background-color: %1").arg(c.name()));
    ui -> colorInfo -> setText(c.name());
}
