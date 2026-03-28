#ifndef TERM_H
#define TERM_H
#include <iomanip>
#include <iostream>
#include <cassert>
using namespace std;

using CoefType = long double;

bool double_equals(CoefType left, CoefType right, CoefType epsilon = 0.0001);

struct Term
{
    CoefType _coef; ///< Coefficient of the term.
    int _exp; ///< Exponent of the term.

    Term();

    Term(CoefType coef, int order);

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

    // Comparison operators

    friend bool operator==(const Term& lhs, const Term& rhs);
    friend bool operator!=(const Term& lhs, const Term& rhs);
    friend bool operator>(const Term& lhs, const Term& rhs);
    friend bool operator<(const Term& lhs, const Term& rhs);
    friend bool operator>=(const Term& lhs, const Term& rhs);
    friend bool operator<=(const Term& lhs, const Term& rhs);

    // Arithmetic operators

    friend Term operator+(const Term& lhs, const Term& rhs);
    friend Term operator-(const Term& lhs, const Term& rhs);
    friend Term operator*(const Term& lhs, const Term& rhs);
    friend Term operator/(const Term& lhs, const Term& rhs);

    // Input/Output stream operators

    friend ostream& operator<<(ostream& outs, const Term& t);
    friend istream& operator>>(istream& ins, Term& t);
};

#endif
