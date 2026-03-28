#include "term.h"
#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;

bool double_equals(CoefType left, CoefType right, CoefType epsilon) {
    if (fabs(left - right) < epsilon) {
        return true;
    }
    // 2. Relative check
    // This scales the epsilon based on the size of the numbers being compared.
    return fabs(left - right) <= epsilon * max(fabs(left), fabs(right));
}

Term::Term(){
    _coef = 0;
    _exp = 0;
}

Term::Term(CoefType coef, int order)
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
    return Term(lhs._coef + rhs._coef, lhs._exp);
}

Term operator-(const Term& lhs, const Term& rhs)
{
    assert(lhs._exp == rhs._exp);
    return Term(lhs._coef - rhs._coef, lhs._exp);
}

Term operator*(const Term& lhs, const Term& rhs)
{
    return Term(lhs._coef * rhs._coef, lhs._exp + rhs._exp);
}

Term operator/(const Term& lhs, const Term& rhs)
{
    assert(!double_equals(rhs._coef, 0.0) && lhs._exp >= rhs._exp);
    return Term(lhs._coef / rhs._coef, lhs._exp - rhs._exp);
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





