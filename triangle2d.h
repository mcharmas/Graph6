#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include <QObject>
#include <QPointF>
#include <QImage>
#include <QPainter>

class Triangle2D : public QObject
{
Q_OBJECT
public:
    Triangle2D(QPointF p1, QPointF p2, QPointF p3, QObject *parent = 0);
    QPointF p1,p2,p3;

    void draw(QPainter *p);

signals:

public slots:

private:


};

#endif // TRIANGLE2D_H
