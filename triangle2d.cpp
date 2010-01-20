#include "triangle2d.h"

Triangle2D::Triangle2D(QPointF p1, QPointF p2, QPointF p3, QObject *parent) : QObject(parent)
    ,p1(p1), p2(p2), p3(p3)
{
}


void Triangle2D::draw(QImage *img, QColor c1, QColor c2, QColor c3)
{
    this->img = img;
    this->c1 = c1;
    this->c2 = c2;
    this->c3 = c3;
    genGradient();

//    QPen p(Qt::black);
//    painter->setPen(p);
//    painter->drawLine(p1, p2);
//    painter->drawLine(p2, p3);
//    painter->drawLine(p1, p3);
//    //QPointF points[]={p1,p2,p3};
    //painter->drawPolygon(points, 3);
}

void Triangle2D::genGradient()
{        
//    QPointF *p1 = new QPointF(this->p1.x(), this->p1.y());
//    QPointF *p2 = new QPointF(this->p2.x(), this->p2.y());
//    QPointF *p3 = new QPointF(this->p3.x(), this->p3.y());

    QPoint *p1 = new QPoint(this->p1.x(), this->p1.y());
    QPoint *p2 = new QPoint(this->p2.x(), this->p2.y());
    QPoint *p3 = new QPoint(this->p3.x(), this->p3.y());


    if(p1->y() > p2->y()) {
        QPoint *tmp = p1;
        p1 = p2;
        p2 = tmp;
        swapColors(c1,c2);
    }

    if(p2->y() > p3->y()) {
        QPoint *tmp = p2;
        p2 = p3;
        p3 = tmp;
        swapColors(c2,c3);
        if(p1->y() > p2->y()) {
             QPoint *tmp = p1;
             p1 = p2;
             p2 = tmp;
             swapColors(c1,c2);
        }
    }

    double delta_xl;
    double delta_xr;
    double xl;
    double xr;

    if ( p1->y() == p2->y() )
    {
        xl = p3->x();
        xr = p3->x();

        delta_xl = (double)(p2->x() - p3->x()) / (double)(p2->y() - p3->y());
        delta_xr = (double)(p1->x() - p3->x()) / (double)(p1->y() - p3->y());

        Rgb colorDeltaL = (Rgb(c3) - Rgb(c2)) / ( p3->y() - p2->y() );

        Rgb colorDeltaR = (Rgb(c3) - Rgb(c1)) / ( p3->y() - p1->y() );

        Rgb colorL(c3);
        Rgb colorR(c3);
        fillLine(p1->x(), c1, p2->x(), c2, p2->y());
        for(int i = p3->y(); i > p2->y(); i--)
        {
            fillLine(xl, colorL.toQColor(), xr, colorR.toQColor(), i);
            colorL = colorL - colorDeltaL;
            colorR = colorR - colorDeltaR;

            xl -= delta_xl;
            xr -= delta_xr;
        }

    }
    else
    {
        delta_xl = (double)(p2->x() - p1->x()) / (double)(p2->y() - p1->y());
        delta_xr = (double)(p3->x() - p1->x()) / (double)(p3->y() - p1->y());
        xl = p1->x();
        xr = p1->x();

        Rgb colorDeltaL = (Rgb(c1) - Rgb(c2)) / ( p1->y() - p2->y() );
        Rgb colorDeltaR = (Rgb(c1) - Rgb(c3)) / ( p1->y() - p3->y() );

        Rgb colorL(c1);
        Rgb colorR(c1);

        for(int i = p1->y(); i < p2->y(); i++)
        {
            fillLine(xl, colorL.toQColor(), xr, colorR.toQColor(), i);

            colorL = colorL + colorDeltaL;
            colorR = colorR + colorDeltaR;

            xl += delta_xl;
            xr += delta_xr;
        }

        if (p3->y() == p2->y())
        {
            fillLine(p3->x(), c3, p2->x(), c2, p3->y());
        }
        else
        {
            delta_xl = (double)(p3->x() - p2->x()) / (double)(p3->y() - p2->y());

            colorDeltaL = (Rgb(c3) - Rgb(c2)) / abs(( p3->y() - p2->y() ));
            for(int i = p2->y() ; i < p3->y(); i++)
            {
                fillLine(xl, colorL.toQColor(), xr, colorR.toQColor(), i);
                colorL = colorL + colorDeltaL;
                colorR = colorR + colorDeltaR;

                xl += delta_xl;
                xr += delta_xr;
            }
        }

    }
}

void Triangle2D::fillLine(int p1, QColor c1, int p2, QColor c2, int y)
{
    if(p2 < p1)
    {
        int tmp = p1;
        p1 = p2;
        p2 = tmp;
        swapColors(c1, c2);
    }
    Rgb delta = (Rgb(c2) - Rgb(c1)) / (p2 - p1);
    Rgb start(c1);

    for(int i = p1; i <= p2; i++)
    {
        img->setPixel(i, y, start.toQColor().rgb());        
        start = start + delta;
    }
}

void Triangle2D::swapColors(QColor &c1, QColor &c2)
{
      QColor tmpC(c1.rgb());
      c1 = QColor(c2.rgb());
      c2 = QColor(tmpC.rgb());
}
