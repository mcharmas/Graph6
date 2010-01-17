#ifndef PICTURE_H
#define PICTURE_H

#include <QWidget>
#include <QPainter>
#include <QMatrix4x4>
#include <QVector4D>
#include <cmath>
#include <QDebug>
#include <QList>
#include <QtAlgorithms>
#include "triangle.h"
#include "triangle2d.h"

class Picture : public QWidget
{
Q_OBJECT
public:
    explicit Picture(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void setTranslateX(int x) { this->translateX = x; update(); }
    void setTranslateY(int x) { this->translateY = x; update(); }
    void setTranslateZ(int x) { this->translateZ = x; update(); }

    void setScaleX(int x) { this->scaleX = x; update(); }
    void setScaleY(int x) { this->scaleY = x; update(); }
    void setScaleZ(int x) { this->scaleZ = x; update(); }

    void setRotateX(int x) { this->rotateX = x; update(); }
    void setRotateY(int x) { this->rotateY = x; update(); }
    void setRotateZ(int x) { this->rotateZ = x; update(); }

    void setDistance(int x) { this->distance = (double)x/10; update(); }
    void setKa(int x) { this->Ka = (double)x/100; update(); }
    void setKd(int x) { this->Kd = (double)x/100; update(); }
    void setKs(int x) { this->Ks = (double)x/100; update(); }

    void setLightX(int x) {light.setX(x); update();}
    void setLightY(int x) {light.setY(x); update();}
    void setLightZ(int x) {light.setZ(x); update();}


private:
    int translateX, translateY, translateZ;
    int scaleX, scaleY, scaleZ;
    int rotateX, rotateY, rotateZ;
    double distance;
    double Ka, Kd, Ks;
    QVector3D light;

    QImage picture;
    QList<Triangle*> triangles;

    QMatrix4x4 getRotateMatrixX(double x);
    QMatrix4x4 getRotateMatrixY(double x);
    QMatrix4x4 getRotateMatrixZ(double x);

    QMatrix4x4 getTranslateMatrix(double x, double y, double z);
    QMatrix4x4 getScaleMatrix(double x, double y, double z);

    QPointF projectPoint(QVector4D p);

    void drawAxis();
    QImage renderTriangles();

    //sphere
    QVector4D getPointOnSphere(double alpha, double beta, double r);
    void generateSphere();
    double angle(QVector3D, QVector3D);

};

#endif // PICTURE_H
