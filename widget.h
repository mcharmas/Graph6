#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "picture.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Widget *ui;
    Picture *pic;
};

#endif // WIDGET_H
