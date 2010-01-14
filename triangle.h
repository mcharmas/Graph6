#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QVector4D>
#include <QDebug>
class Triangle : public QObject
{
Q_OBJECT
public:
    Triangle(QVector4D p1, QVector4D p2, QVector4D p3, QObject *parent = 0);
    QVector4D p1, p2 ,p3;
    void debug();

signals:

public slots:

private:



};

#endif // TRIANGLE_H
