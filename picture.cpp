#include "picture.h"
#define PI 3.14159265

Picture::Picture(QWidget *parent) :
    QWidget(parent), translateX(0),  translateY(0),  translateZ(0),
    scaleX(100), scaleY(100), scaleZ(100),
    rotateX(0), rotateY(0), rotateZ(0)
{
    picture = QImage(600, 400, QImage::Format_ARGB32);
    picture.fill(qRgb(0,0,0));
    triangles = QVector<Triangle*>();
    generateSphere();

    distance = 2;
    Ka = 0.5;
    Kd = 0.5;
    Ks = 0.5;
    //lightPosition = QVector4D(0,0,0,1);
    //viewerPosition = QVector4D(0,0,1,1);
    lightPosition = QVector4D(0,0,0,1);
    viewerPosition = QVector4D(0,0,-1000,1);

    sceneAngleX = 0;
    sceneAngleY = 0;    

}

void Picture::paintEvent(QPaintEvent *)
{

    QPainter p(this);
    p.drawImage(0,0,renderTriangles().scaled(this->size(), Qt::KeepAspectRatio));
}

bool lessThan(const Triangle* p1, const Triangle* p2)
{
    return p1->p1.z() < p2->p1.z();
}


QImage Picture::renderTriangles()
{
    QImage tmp = picture;

    // tutaj obracam wszystkie trojkaty
    QMatrix4x4 translate = getTranslateMatrix(translateX, translateY, translateZ);
    QMatrix4x4 scale = getScaleMatrix((double)scaleX/100, (double)scaleY/100, (double)scaleZ/100);    
    QMatrix4x4 rX = getRotateMatrixX((double)rotateX * PI / 180);
    QMatrix4x4 rY = getRotateMatrixY((double)rotateY * PI / 180);
    QMatrix4x4 rZ = getRotateMatrixZ((double)rotateZ * PI / 180);
    QMatrix4x4 transform = translate * scale * rX * rY * rZ;
    QVector<Triangle*> trans;
    for(QVector<Triangle*>::iterator it = triangles.begin(); it != triangles.end(); it++)
    {
        QVector4D np1((*it)->p1 * transform);
        QVector4D np2((*it)->p2 * transform);
        QVector4D np3((*it)->p3 * transform);        
        Triangle *t = new Triangle(np1, np2, np3, (*it)->isUpsideDown);
        trans.append(t);
    }
    //koncze obracac



    QPainter painter(&tmp);

    QVector4D lPos(lightPosition);
    QVector4D viewerPos(viewerPosition);
    rotateScene(trans, lPos, viewerPos); //tutaj obracam cala scene

    double Ia = 0.5;//naterzenie swiatla
    double m = 2;
    QColor color(255,255,0);//wejsciowy kolor kuli
    qSort(trans.begin(), trans.end(), lessThan); //sortuje zeby mi trojkaty z tylu nie zaslanialy tych z przodu...
    for(QVector<Triangle*>::iterator it = trans.begin(); it != trans.end(); it++)
    {
        Triangle* t3d(*it);        
        QVector3D n = t3d->normal();
        QVector3D l(lPos.toVector3D());
        l = t3d->p1.toVector3D() - l;
        double dist = l.length();
        l.normalize();

        double ang = (angle(n, l));

        QVector3D z; // to niby jakies swiatlo odbite
        z.setX(2*n.x() * ang - l.x());
        z.setY(2*n.y() * ang - l.y());
        z.setZ(2*n.z() * ang - l.z());

        QVector3D e(viewerPos);
        e = e - t3d->p1.toVector3D();
        e.normalize();

        double I = Ka * Ia + (Kd * ang + Ks * std::pow(angle(e, z), 5)) / (dist/80);

        //qDebug() << n.x() << l.x() << e.x() << z.x();
        QColor c;
        if (I > 0)
        {
            int r = qMin(int(color.red()*I), 255);
            int g = qMin(int(color.green()*I),255);
            int b = qMin(int(color.blue()*I), 255);
            c = QColor(r,g,b);
        }
        else
        {
            c = QColor(0,0,0);
        }

        QPen pen(c, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        QBrush brush(c);
        painter.setPen(pen);
        painter.setBrush(brush);

        Triangle2D t(projectPoint(t3d->p1), projectPoint(t3d->p2), projectPoint(t3d->p3));
        t.draw(&painter);                       

        delete t3d;
    }    
    QBrush brush(qRgb(255,0,0));
    painter.setBrush(brush);
    painter.drawEllipse(projectPoint(lPos), 5, 5);

    return tmp;
}

void Picture::rotateScene(QVector<Triangle*> &triangles, QVector4D &light, QVector4D &v)
{
    QMatrix4x4 rotateY = getRotateMatrixY((double)sceneAngleY * PI / 180);
    QMatrix4x4 rotateX = getRotateMatrixX((double)sceneAngleX * PI / 180);
    QMatrix4x4 transform = rotateX * rotateY;
 ;   for(int i=0; i<triangles.size(); i++)
    {
        triangles[i]->p1 = triangles[i]->p1 * transform;
        triangles[i]->p2 = triangles[i]->p2 * transform;
        triangles[i]->p3 = triangles[i]->p3 * transform;
    }
    light= light * transform;
    //v = v * transform;

}

double Picture::angle(QVector3D v1, QVector3D v2)
{    
    v1.normalize();
    v2.normalize();
    return QVector3D::dotProduct(v1, v2);
}

QVector4D Picture::getPointOnSphere(double alpha, double beta, double r)
{
    QVector4D p(0,r,0,1);
    QMatrix4x4 rX = getRotateMatrixX((double)beta * PI / 180);
    QMatrix4x4 rY = getRotateMatrixY((double)alpha * PI / 180);    
    QMatrix4x4 transform(rX * rY);

    return p * transform;
}

void Picture::generateSphere()
{
    for (int i=0; i<360; i+=15)
    {
        for (int j=0; j<180; j+=15)
        {
            QVector4D p00(getPointOnSphere(i, j, 100));
            QVector4D pRG(getPointOnSphere(i+7.5, j+15, 100));
            QVector4D pLG(getPointOnSphere(i-7.5, j+15, 100));
            QVector4D pRD(getPointOnSphere(i+15, j, 100));
            Triangle *n1 = new Triangle(p00, pRD ,pRG, this);
            Triangle *n2 = new Triangle(p00 ,pRG ,pLG, this);
            //n2->isUpsideDown = false;
            triangles.append(n1);
            triangles.append(n2);
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
    QPen pen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
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
    p.setY((p.y())/* + picture.height()/2*/);
    p.setX((p.x())/* + picture.width()/2*/);
    p.setZ(p.z());

    double d = 1000;
    double x = (p.x() * d) / (p.z() + d);
    double y = (p.y() * d) / (p.z() + d);

    //qDebug() << p;
    //qDebug() << QPointF(x,y);
    return QPointF(x+picture.width()/2,y+picture.height()/2);
    //return QPointF(x,y);

    //QVector4D p1 = p * getTranslateMatrix(-picture.height()/2, -picture.width()/2,0).inverted(NULL);
    //double d = 1000;
    //double x = (p.x() * d) / (p.z() + d);
    //double y = (p.y() * d) / (p.z() + d);
    //return QPointF(x,y);
}
