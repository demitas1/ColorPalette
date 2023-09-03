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
}

Widget::~Widget()
{
    delete ui;
}

