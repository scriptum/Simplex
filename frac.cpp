#include "frac.h"
#include <QtGlobal>
frac::frac()
{
    n = d = 1;
}

frac::frac(long _n)
{
    d = 1;
    n = _n;
}

frac::frac(long _n, long _d)
{
    if(_d == 0)
        _d = 1;
    if(_d < 0)
    {
        d = -_d;
        n = -_n;
    }
    else
    {
        n = _n;
        d = _d;
    }
    simple();
}

QString frac::str()
{
    if(d != 1)
        return QString::number(n) + "/" + QString::number(d);
    else
        return QString::number(n);
}

frac frac::operator - ()
{
    n = -n;
    return *this;
}

frac frac::operator + (const frac a)
{
    return frac(n * a.d + a.n * d, d * a.d);
}

frac frac::operator - (const frac a)
{
    return frac(n * a.d - a.n * d, d * a.d);
}

frac frac::operator * (const frac a)
{
    return frac(n*a.n,d*a.d);
}

frac frac::operator / (const frac a)
{
    return frac(n * a.d, d * a.n);
}

void frac::simple()
{
    long a = qMax(qAbs(n),d), b = qMin(qAbs(n),d), m;
    while (b > 0)
    {
        m = a % b;
        a = b;
        b = m;
    }
    n /= a;
    d /= a;
}

bool frac::operator == (const frac a)
{
    return (a.n==n)&&(a.d==d);
}

bool frac::operator > (const frac a)
{
    return n*a.d > a.n*d;
}

bool frac::operator < (const frac a)
{
    return n*a.d < a.n*d;
}

bool frac::operator >= (const frac a)
{
    return n*a.d >= a.n*d;
}

bool frac::operator <= (const frac a)
{
    return n*a.d <= a.n*d;
}
