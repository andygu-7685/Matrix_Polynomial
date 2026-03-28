#include "term.h"
#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;

bool double_equals(double left, double right, double epslion)
{
    return fabs(left - right) < epslion ? true : false;
}

Term::Term(){
    _coef = 0;
    _exp = 0;
}

Term::Term(double coef, int order)
{
    _coef = coef;
    _exp = order;
}

bool operator==(const Term& lhs, const Term& rhs)
{
    return lhs._exp == rhs._exp;
}

bool operator!=(const Term& lhs, const Term& rhs)
{
    return !(lhs == rhs);
}

bool operator>(const Term& lhs, const Term& rhs)
{
    return lhs._exp > rhs._exp;
}

bool operator<(const Term& lhs, const Term& rhs)
{
    return lhs._exp < rhs._exp;
}

bool operator>=(const Term& lhs, const Term& rhs)
{
    return lhs._exp >= rhs._exp;
}

bool operator<=(const Term& lhs, const Term& rhs)
{
    return lhs._exp <= rhs._exp;
}

Term operator+(const Term& lhs, const Term& rhs)
{
    assert(lhs._exp == rhs._exp);
    Term temp = Term(lhs._coef + rhs._coef, lhs._exp);
    return temp;
}

Term operator-(const Term& lhs, const Term& rhs)
{
    assert(lhs._exp == rhs._exp);
    Term temp = Term(lhs._coef - rhs._coef, lhs._exp);
    return temp;
}

Term operator*(const Term& lhs, const Term& rhs)
{
    Term temp = Term(lhs._coef * rhs._coef, lhs._exp + rhs._exp);
    return temp;
}

Term operator/(const Term& lhs, const Term& rhs)
{
    assert(!double_equals(rhs._coef, 0.0) && lhs._exp >= rhs._exp);
    Term temp = Term(lhs._coef / rhs._coef, lhs._exp - rhs._exp);
    return temp;
}

ostream& operator<<(ostream& outs, const Term& t)
{
    if (t._exp > 1)
    {
        outs << showpos << fixed << setprecision(1) << t._coef << noshowpos << "x^" << t._exp;
    }
    else if (t._exp == 1)
    {
        outs << showpos << fixed << setprecision(1) << t._coef << noshowpos << "x";
    }
    else
    {
        outs << showpos << fixed << setprecision(1) << t._coef;
    }
    return outs;
}

istream& operator>>(istream& ins, Term& t)
{
    return ins >> t._coef >> t._exp;
}