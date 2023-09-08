#include "widget.h"
#include "mypalette/mypalette.h"
#include "current_color/current_color.h"
#include "./ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui -> setupUi(this);

    ui -> colorPalette -> loadDefaultColors();
    paletteColorPicked();

    connect(
        ui -> colorPalette,
        &MyPalette::colorPicked,
        this,
        [=] () {
            paletteColorPicked();
        });

    connect(
        ui -> colorPalette,
        &MyPalette::backgroundColorPicked,
        this,
        [=] () {
            paletteBackgroundColorPicked();
        });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paletteColorPicked()
{
    // pick a color from palette to display in current color
    QColor c = ui -> colorPalette -> currentColor();
    qInfo() << "palette color is picked." << c.name();
    ui -> currentColor2 -> setForegroundColor(c);

    // test of color picker
    ui -> colorPicker -> setColor(c);
}

void Widget::paletteBackgroundColorPicked()
{
    // pick a color from palette to display in current color
    QColor c = ui -> colorPalette -> currentBackgroundColor();
    qInfo() << "palette color is picked." << c.name();
    ui -> currentColor2 -> setBackgroundColor(c);
}
