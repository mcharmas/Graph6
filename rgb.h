#ifndef RGB_H
#define RGB_H
#include <QColor>
#include "math.h"

class Rgb
{
public:
    Rgb(double, double, double);
    Rgb(QColor c);
    Rgb(const Rgb& r1);
    double r() const { return rv; }
    double g() const  { return gv; }
    double b() const  { return bv; }
    Rgb& operator-(Rgb r1);
    Rgb& operator+(Rgb r1);
    Rgb& operator=(Rgb r1);
    Rgb& operator/(double r1);
    Rgb& operator*(double r1);

    void rabs() { fabs(rv); fabs(gv); fabs(bv); }


    QColor toQColor() { return QColor(rv, gv,bv); }

    double rv;
    double gv;
    double bv;

};

#endif // RGB_H
