#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "../../includes/node/node.h"
#include "../../includes/list_sorted/list_sorted.h"
#include "../../includes/linear_algebra/matrix.h"
#include "../../includes/linear_algebra/vector.h"
#include "term.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using VarType = Matrix<double>;

class polynomial
{
public:

    polynomial();
    polynomial(CoefType* term_array, int order);
    polynomial(const vector<CoefType>& terms);
    polynomial(CoefType c, unsigned int exponent = 0);
    polynomial(const polynomial& source);
    polynomial& operator=(const polynomial& RHS);
    polynomial& operator=(const CoefType& RHS);
    ~polynomial();
    void remove_zeros();
    friend bool test_equal(polynomial left, polynomial right);
    void add_to_coef(CoefType amount, unsigned int exponent);
    void assign_coef(CoefType coefficient, unsigned int exponent);
    unsigned int next_term(unsigned int e) const;
    unsigned int previous_term(unsigned int e) const;
    polynomial derivative() const;
    VarType eval(VarType x) const;
    void find_root(CoefType& answer,
                    bool& success,
                    unsigned int& iterations,
                    CoefType guess = 0,
                    unsigned int maximum_iterations = 100,
                    CoefType epsilon = 1e-8) const;
    void clear();
    bool find(const int exp);
    polynomial& operator+=(const Term& t);
    polynomial& operator*=(const Term& t);
    polynomial& operator+=(const polynomial& RHS);
    polynomial& operator*=(const polynomial& RHS);
    polynomial& operator-=(const polynomial& RHS);
    polynomial operator-() const;
    VarType operator()(VarType x) const { return eval(x); }
    friend bool operator==(const polynomial& left, const polynomial& right);
    friend bool operator!=(const polynomial& left, const polynomial& right);
    friend polynomial operator+(const polynomial& left, const polynomial& right);
    friend polynomial operator-(const polynomial& left, const polynomial& right);
    friend polynomial operator*(const polynomial& left, const polynomial& right);
    friend polynomial operator/(const polynomial& left, const polynomial& right);
    friend polynomial operator%(const polynomial& left, const polynomial& right);
    friend polynomial operator+(const polynomial& left, const Term& t);
    friend polynomial operator*(const polynomial& left, const Term& t);
    friend ostream& operator<<(ostream& outs, const polynomial& print_me);
    friend istream& operator>>(istream& ins, polynomial& read_me);
    const Term& operator[](const int exp) const;
    Term& operator[](const int exp);
    List<Term> list() const;
    int order() const;
    CoefType coefficient(unsigned int exponent) const;
    unsigned int degree() const;
private:
    List<Term> _poly; 
    int _order; 
    node<Term>* head_ptr; 
    node<Term>* tail_ptr; 
    mutable node<Term>* recent_ptr; 
    void set_recent(unsigned int exponent) const; 
};
#endif