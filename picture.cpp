#include "picture.h"
#define PI 3.14159265

Picture::Picture(QWidget *parent) :
    QWidget(parent), translateX(0),  translateY(0),  translateZ(0),
    scaleX(100), scaleY(100), scaleZ(100),
    rotateX(0), rotateY(0), rotateZ(0)
{
    picture = QImage(600, 400, QImage::Format_ARGB32);
    picture.fill(qRgb(255,255,255));
    //drawAxis();
    triangles = QList<Triangle*>();
//    triangles.append(new Triangle(QVector4D(5,5,5,1), QVector4D(80,0,0,1), QVector4D(0,80,0,1), this));
    generateSphere();
}

void Picture::paintEvent(QPaintEvent *)
{

    QPainter p(this);
    p.drawImage(0,0,renderTriangles().scaled(this->size(), Qt::KeepAspectRatio));
}

QImage Picture::renderTriangles()
{
    QImage tmp = picture;

    QMatrix4x4 translate = getTranslateMatrix(translateX, translateY, translateZ);
    QMatrix4x4 scale = getScaleMatrix((double)scaleX/100, (double)scaleY/100, (double)scaleZ/100);    
    QMatrix4x4 rX = getRotateMatrixX((double)rotateX * PI / 180);
    QMatrix4x4 rY = getRotateMatrixY((double)rotateY * PI / 180);
    QMatrix4x4 rZ = getRotateMatrixZ((double)rotateZ * PI / 180);

    bool dupa;
    QMatrix4x4 transform = translate.inverted(&dupa) * scale.inverted(&dupa) * rX.inverted(&dupa) * rY.inverted(&dupa) * rZ.inverted(&dupa);

    QPainter painter(&tmp);
    QPen pen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    for(QList<Triangle*>::iterator it = triangles.begin(); it != triangles.end(); it++)
    {

        QVector4D np1((*it)->p1 * transform);
        QVector4D np2((*it)->p2 * transform);
        QVector4D np3((*it)->p3 * transform);

        painter.drawLine(projectPoint(np1), projectPoint(np2));
        painter.drawLine(projectPoint(np1), projectPoint(np3));
        painter.drawLine(projectPoint(np2), projectPoint(np3));
    }

    return tmp;
}

QVector4D Picture::getPointOnSphere(double alpha, double beta, double r)
{
    QVector4D p(0,r,0,1);
    //QMatrix4x4 translate = getTranslateMatrix(r, 0, 0);
    QMatrix4x4 rX = getRotateMatrixX((double)beta * PI / 180);
    QMatrix4x4 rY = getRotateMatrixY((double)alpha * PI / 180);
    qDebug() << p << p*rX;
    QMatrix4x4 transform(rX * rY);

    return p * transform;
}

void Picture::generateSphere()
{    
    for (int i=0; i<360; i+=15)
    {
        for (int j=0; j<180; j+=15)
        {
            Triangle *n = new Triangle(getPointOnSphere(i, j, 100),getPointOnSphere(i+15, j, 100),getPointOnSphere(i+7.5, j+15, 100), this);
            n->debug();
            triangles.append(n);
        }
    }
}

void Picture::drawAxis()
{
    QVector4D oo(0,0,0,0);
    QVector4D ox(180,0,0,0);
    QVector4D oy(0,180,0,0);
    QVector4D oz(0,0,1800,0);


    QPainter p(&picture);
    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen);
    //p.setRenderHint(QPainter::Antialiasing, true);
    //p.setRenderHint(QPainter::HighQualityAntialiasing, true);
    p.drawLine(projectPoint(oo), projectPoint(ox));
    p.drawLine(projectPoint(oo), projectPoint(oy));
    p.drawLine(projectPoint(oo), projectPoint(oz));

}

QMatrix4x4 Picture::getRotateMatrixZ(double x)
{    
    QMatrix4x4 m(cos(x), sin(x), 0, 0,
                 -sin(x), cos(x), 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1
                 );
    return m;
}

QMatrix4x4 Picture::getRotateMatrixX(double x)
{    
    QMatrix4x4 m(1, 0, 0, 0,
                 0, cos(x), sin(x), 0,
                 0, -sin(x), cos(x), 0,
                 0, 0, 0, 1
                 );
    return m;
}

QMatrix4x4 Picture::getRotateMatrixY(double x)
{
    QMatrix4x4 m(cos(x), 0, -sin(x), 0,
                 0, 1, 0, 0,
                 sin(x), 0, cos(x), 0,
                 0, 0, 0, 1
                 );
    return m;
}


QMatrix4x4 Picture::getTranslateMatrix(double x, double y, double z)
{
    QMatrix4x4 m(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 x, y, z, 1
                 );
    return m;
}

QMatrix4x4 Picture::getScaleMatrix(double x, double y, double z)
{
    QMatrix4x4 m(x, 0, 0, 0,
                 0, y, 0, 0,
                 0, 0, z, 0,
                 0, 0, 0, 1
                 );
    //qDebug() << x << y << z;
    return m;
}

QPointF Picture::projectPoint(QVector4D p)
{    
    p.setY((-p.y()) + picture.height()/2);
    p.setX((-p.x()) + picture.width()/2);
    p.setZ(p.z());

    double d = 1000;
    double x = (p.x() * d) / (p.z() + d);
    double y = (p.y() * d) / (p.z() + d);

    //qDebug() << p;
    //qDebug() << QPointF(x,y);
    //return QPointF(x+picture.width()/2,y+picture.height()/2);
    return QPointF(x,y);

    //QVector4D p1 = p * getTranslateMatrix(-picture.height()/2, -picture.width()/2,0).inverted(NULL);
    //double d = 1000;
    //double x = (p.x() * d) / (p.z() + d);
    //double y = (p.y() * d) / (p.z() + d);
    //return QPointF(x,y);
}
