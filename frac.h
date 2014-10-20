#ifndef FRAC_H
#define FRAC_H
#include <QString>
class frac
{
private:
    long n, d;
    void simple();
public:
    //nominator & denominator

    frac();
    frac(long);
    frac(long, long);
    frac operator - ();
    frac operator + (const frac);
    frac operator - (const frac);
    frac operator * (const frac);
    frac operator / (const frac);
    bool operator == (const frac);
    bool operator > (const frac);
    bool operator < (const frac);
    bool operator >= (const frac);
    bool operator <= (const frac);
    QString str();
};



#endif // FRAC_H
