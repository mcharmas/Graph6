#include "triangle.h"

Triangle::Triangle(QVector4D p1, QVector4D p2, QVector4D p3, QObject *parent) :
    QObject(parent) , p1(p1), p2(p2), p3(p3)
{
}

void Triangle::debug()
{
    qDebug() << p1<< p2 << p3;
}
