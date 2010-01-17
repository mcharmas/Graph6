#include "triangle2d.h"

Triangle2D::Triangle2D(QPointF p1, QPointF p2, QPointF p3, QObject *parent) : QObject(parent)
    ,p1(p1), p2(p2), p3(p3)
{
}


void Triangle2D::draw(QPainter* painter)
{
    //painter->drawLine(p1, p2);
    //painter->drawLine(p2, p3);
    //painter->drawLine(p1, p3);
    QPointF points[]={p1,p2,p3};
    painter->drawPolygon(points, 3);
}
