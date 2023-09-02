#include "widget.h"
#include "mypalette.h"
#include "./ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //MyPalette *myPalette = new MyPalette(this);
}

Widget::~Widget()
{
    delete ui;
}

