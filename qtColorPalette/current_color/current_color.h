#ifndef CURRENT_COLOR_H
#define CURRENT_COLOR_H

#include <QWidget>

namespace Ui {
class CurrentColor;
}

class CurrentColor : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentColor(QWidget *parent = nullptr);
    ~CurrentColor();

    void setForegroundColor(QColor c);

private:
    Ui::CurrentColor *ui;
};

#endif // CURRENT_COLOR_H
