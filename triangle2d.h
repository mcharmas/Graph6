#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include <QObject>
#include <QPointF>
#include <QImage>
#include <QPainter>
#include "rgb.h"

class Triangle2D : public QObject
{
Q_OBJECT
public:
    Triangle2D(QPointF p1, QPointF p2, QPointF p3, QObject *parent = 0);
    QPointF p1,p2,p3;
    QColor c1, c2, c3;
    void fillLine(int p1, QColor c1, int p2, QColor c2, int y);
    void swapColors(QColor &c1, QColor &c2);

    void genGradient();

    void draw(QImage*, QColor, QColor, QColor);

signals:

public slots:

private:
    QImage *img;


};

#endif // TRIANGLE2D_H
