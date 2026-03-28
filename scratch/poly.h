#ifndef POLY_H
#define POLY_H
#include "../../includes/node/node.h"
#include "../../includes/list_sorted/list_sorted.h"
#include "term.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class Poly
{
public:
    Poly();
    Poly(double* term_array, int order);
    Poly(const vector<double>& terms);
    Poly(double c, unsigned int exponent = 0);
    Poly(const Poly& source);
    Poly& operator=(const Poly& RHS);
    Poly& operator=(const double& RHS);
    ~Poly();
    void remove_zeros();
    friend bool test_equal(Poly left, Poly right);
    void add_to_coef(double amount, unsigned int exponent);
    void assign_coef(double coefficient, unsigned int exponent);
    unsigned int next_term(unsigned int e) const;
    unsigned int previous_term(unsigned int e) const;
    Poly derivative( ) const;
    double eval(double x) const;
    void find_root( double& answer,
                    bool& success,
                    unsigned int& iterations,
                    double guess = 0,
                    unsigned int maximum_iterations = 100,
                    double epsilon = 1e-8 ) const;
    void clear();
    Poly& operator+=(const Term& t);
    Poly& operator*=(const Term& t);
    Poly& operator+=(const Poly& RHS);
    Poly& operator*=(const Poly& RHS);
    Poly& operator-=(const Poly& RHS);
    Poly operator-() const;
    double operator() (double x) const { return eval(x); }
    friend bool operator==(const Poly& left, const Poly& right);
    friend bool operator!=(const Poly& left, const Poly& right);
    friend Poly operator+(const Poly& left, const Poly& right);
    friend Poly operator-(const Poly& left, const Poly& right);
    friend Poly operator*(const Poly& left, const Poly& right);
    friend Poly operator/(const Poly& left, const Poly& right);
    friend Poly operator%(const Poly& left, const Poly& right);
    friend Poly operator+(const Poly& left, const Term& t);
    friend Poly operator*(const Poly& left, const Term& t);
    friend ostream& operator<<(ostream& outs, const Poly& print_me);
    friend istream& operator>>(istream& ins, Poly& read_me);
    const Term& operator[](const int exp) const;
    Term& operator[](const int exp);
    List<Term> list() const;
    int order() const;
    double coefficient(unsigned int exponent) const;
    unsigned int degree( ) const;
private:
    List<Term> _poly;
    int _order;
    node<Term>* head_ptr;
    node<Term>* tail_ptr;
    mutable node<Term>* recent_ptr;
    void set_recent(unsigned int exponent) const;
};
#endif 