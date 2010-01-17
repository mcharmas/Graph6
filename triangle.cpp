#include "triangle.h"

Triangle::Triangle(QVector4D p1, QVector4D p2, QVector4D p3, bool isUpsideDown, QObject *parent) :
    QObject(parent) , p1(p1), p2(p2), p3(p3), isUpsideDown(isUpsideDown)
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
    if (isUpsideDown)
    {
        //qDebug() << "upsideDown " << QVector3D::normal(p1.toVector3D(), p2.toVector2D(), p3.toVector3D());
        //return QVector3D::normal(p1.toVector3D(), p2.toVector2D(), p3.toVector3D());
    }    
    //qDebug() << "normal" <<  QVector3D::normal(p3.toVector3D(), p2.toVector2D(), p1.toVector3D());
    return QVector3D::normal(p3.toVector3D(), p2.toVector2D(), p1.toVector3D());
}

Triangle Triangle::operator=(const Triangle& t)
{
    Triangle t1(t);    
    return t1;
}

bool Triangle::operator <(const Triangle& t) const
{
    bool dupa = qMin(qMin(p1.z(),p2.z()),p3.z()) < qMin(qMin(t.p1.z(),t.p2.z()),t.p3.z());
    qDebug() << qMin(qMin(p1.z(),p2.z()),p3.z()) << " " << qMin(qMin(t.p1.z(),t.p2.z()),t.p3.z()) << dupa;
    return qMin(qMin(p1.z(),p2.z()),p3.z()) < qMin(qMin(t.p1.z(),t.p2.z()),t.p3.z());
}
