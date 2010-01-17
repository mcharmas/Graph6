#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QVector4D>
#include <QDebug>
#include <cmath>
#include <QVector2D>
#include <QVector3D>
class Triangle : public QObject
{
Q_OBJECT
public:
    Triangle(QVector4D p1, QVector4D p2, QVector4D p3, bool isUpsideDown = false, QObject *parent = 0);
    Triangle(const Triangle&);
    QVector4D p1, p2 ,p3;
    void debug();
    QVector3D normal();
    Triangle operator=(const Triangle&);
    bool operator<(const Triangle&) const;
    bool isUpsideDown;

signals:

public slots:

private:



};

#endif // TRIANGLE_H
