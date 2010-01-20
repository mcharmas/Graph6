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
    Triangle();
    QVector4D p1, p2 ,p3;
    void debug();
    QVector3D normal();
    Triangle operator=(const Triangle&);
    bool operator<(Triangle) const;
    bool isUpsideDown;
    bool has(QVector4D p) { return (eq(p,p1) || eq(p,p2) || eq(p,p3)); }

signals:

public slots:

private:
    bool eq(QVector4D, QVector4D);



};

#endif // TRIANGLE_H
