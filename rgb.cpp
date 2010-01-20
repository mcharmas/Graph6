#include "rgb.h"

Rgb::Rgb(double r, double g, double b)
{
    this->rv  = r;
    this->gv  = g;
    this->bv  = b;
}

Rgb::Rgb(QColor c)
{
    int r,g,b;
    c.getRgb(&r,&g,&b);
    this->rv = r;
    this->gv = g;
    this->bv = b;
}

Rgb::Rgb(const Rgb& r1)
{
    rv = r1.r();
    gv = r1.g();
    bv = r1.b();
}

Rgb& Rgb::operator+(Rgb r1)
{
    this->rv += r1.r();
    this->gv += r1.g();
    this->bv += r1.b();

    rabs();
    return *this;
}

Rgb& Rgb::operator-(Rgb r1)
{
    this->rv -= r1.r();
    this->gv -= r1.g();
    this->bv -= r1.b();

    rabs();
    return *this;
}

Rgb& Rgb::operator=(Rgb r1)
{
    this->rv = r1.r();
    this->gv = r1.g();
    this->bv = r1.b();

    return *this;
}

Rgb& Rgb::operator/(double d)
{
    rv /= d;
    gv /= d;
    bv /= d;
    return *this;
}

Rgb& Rgb::operator*(double d)
{
    rv *= d;
    gv *= d;
    bv *= d;
    return *this;
}
