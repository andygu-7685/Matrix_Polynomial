#ifndef TERM_H
#define TERM_H
#include <iomanip>
#include <iostream>
#include <cassert>
using namespace std;

bool double_equals(double left, double right, double epslion = 0.000001);

struct Term
{
    double _coef;
    int _exp;

    Term();
    Term(double coef, int order);

    Term& operator+=(const Term& rhs)
    {
        assert(_exp == rhs._exp);
        _coef += rhs._coef;
        return *this;
    }

    Term& operator-=(const Term& rhs)
    {
        assert(_exp == rhs._exp);
        _coef -= rhs._coef;
        return *this;
    }

    Term& operator*=(const Term& rhs)
    {
        _coef *= rhs._coef;
        _exp += rhs._exp;
        return *this;
    }

    Term& operator/=(const Term& rhs)
    {
        assert(!double_equals(rhs._coef, 0.0) && this->_exp >= rhs._exp);
        _coef /= rhs._coef;
        _exp -= rhs._exp;
        return *this;
    }

    Term operator-() const
    {
        return Term(-_coef, _exp);
    }

    Term& operator=(const Term& RHS)
    {
        _coef = RHS._coef;
        _exp = RHS._exp;
        return *this;
    }

    friend bool operator==(const Term& lhs, const Term& rhs);
    friend bool operator!=(const Term& lhs, const Term& rhs);
    friend bool operator>(const Term& lhs, const Term& rhs);
    friend bool operator<(const Term& lhs, const Term& rhs);
    friend bool operator>=(const Term& lhs, const Term& rhs);
    friend bool operator<=(const Term& lhs, const Term& rhs);

    friend Term operator+(const Term& lhs, const Term& rhs);
    friend Term operator-(const Term& lhs, const Term& rhs);
    friend Term operator*(const Term& lhs, const Term& rhs);
    friend Term operator/(const Term& lhs, const Term& rhs);

    friend ostream& operator<<(ostream& outs, const Term& t);
    friend istream& operator>>(istream& ins, Term& t);
};

#endif