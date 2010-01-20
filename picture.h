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
#include <QVector3D>
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
    void setScaleY(int x) { this->sceneAngleX = x; update(); }
    void setScaleZ(int x) { this->sceneAngleY = x; update(); }

    void setRotateX(int x) { this->rotateX = x; update(); }
    void setRotateY(int x) { this->rotateY = x; update(); }
    void setRotateZ(int x) { this->rotateZ = x; update(); }

    void setDistance(int x) { this->distance = (double)x/10; update(); }
    void setKa(int x) { this->Ka = (double)x/100; update(); }
    void setKd(int x) { this->Kd = (double)x/100; update(); }
    void setKs(int x) { this->Ks = (double)x/100; update(); }

    void setLightX(int x) {lightPosition.setX(x); update();}
    void setLightY(int x) {lightPosition.setY(x); update();}
    void setLightZ(int x) {lightPosition.setZ(x); update();}


private:
    QImage picture;
    QVector<Triangle*> triangles;

    //translacje
    int translateX, translateY, translateZ;
    int scaleX, scaleY, scaleZ;
    int rotateX, rotateY, rotateZ;

    //oswietlenie
    double distance;
    double Ka, Kd, Ks;
    QVector4D lightPosition;

    //widok
    int sceneAngleX;
    int sceneAngleY;
    QVector4D viewerPosition;


    //funkcje translacji
    QMatrix4x4 getRotateMatrixX(double x);
    QMatrix4x4 getRotateMatrixY(double x);
    QMatrix4x4 getRotateMatrixZ(double x);
    QMatrix4x4 getTranslateMatrix(double x, double y, double z);
    QMatrix4x4 getScaleMatrix(double x, double y, double z);


    //rotacja sceny
    void rotateScene(QVector<Triangle*> &triangles, QVector4D &light, QVector4D &v);

    //dodatkowe
    void drawAxis();
    QImage renderTriangles();
    QPointF projectPoint(QVector4D p);

    //sphere
    QVector4D getPointOnSphere(double alpha, double beta, double r);
    void generateSphere();
    double angle(QVector3D, QVector3D);    

};

#endif // PICTURE_H
