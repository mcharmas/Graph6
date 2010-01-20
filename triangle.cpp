#include "triangle.h"

Triangle::Triangle(QVector4D p1, QVector4D p2, QVector4D p3, bool isUpsideDown, QObject *parent) :
    QObject(parent) , p1(p1), p2(p2), p3(p3), isUpsideDown(isUpsideDown)
{

}

Triangle::Triangle() : QObject(NULL)
{
}

Triangle::Triangle(const Triangle &t) : QObject(t.parent())
{
    p1 = QVector4D(t.p1);
    p2 = QVector4D(t.p2);
    p3 = QVector4D(t.p3);
    this->isUpsideDown = t.isUpsideDown;
}

void Triangle::debug()
{
    qDebug() << p1<< p2 << p3;
}

QVector3D Triangle::normal()
{
    QVector3D w1 = p1.toVector3D() - p2.toVector3D();
    QVector3D w2 = p1.toVector3D() - p3.toVector3D();
    QVector3D norm = QVector3D::crossProduct(w1, w2);
    norm.normalize();
    return norm;
}

Triangle Triangle::operator=(const Triangle& t)
{
    Triangle t1(t);    
    return t1;
}

bool Triangle::operator<(Triangle t) const
{
    return this->p1.z() > t.p1.z();
}

bool Triangle::eq(QVector4D p1, QVector4D p2)
{
    QVector4D p = p1 - p2;
    if (p.length() < 2)
        return true;
    return false;
}
