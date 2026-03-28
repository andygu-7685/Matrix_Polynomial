#ifndef POLYNOMIAL_V1_H
#define POLYNOMIAL_V1_H


// #include "../../includes/node/node.h"
// #include "../../includes/list_sorted/list_sorted.h"
// #include "term.h"
// #include <iostream>
// #include <vector>
// #include <cmath>


// using namespace std;


// class polynomial
// {
// public:
//     // Default constructor for a polynomial object.
//     // Parameters: None.
//     // Return: Initializes a polynomial object with default values.
//     polynomial();
//     // Constructor that initializes a polynomial using a term array and order.
//     // Parameters: 
//     //    term_array - Array of double values representing polynomial coefficients.
//     //    order - Integer representing the order of the polynomial.
//     // Return: A polynomial object initialized with the given terms and order.
//     polynomial(double* term_array, int order);
//     // Constructor that initializes a polynomial using a vector of terms.
//     // Parameters: terms - A vector of doubles representing polynomial coefficients.
//     // Return: A polynomial object initialized with the given terms.
//     polynomial(const vector<double>& terms);
//     polynomial(double c, unsigned int exponent = 0);
//     polynomial(const polynomial& source);
//     polynomial& operator=(const polynomial& RHS);
//     polynomial& operator=(const double& RHS);
//     ~polynomial();


//     void remove_zeros();
//     friend bool test_equal(polynomial left, polynomial right);
//     void add_to_coef(double amount, unsigned int exponent);
//     void assign_coef(double coefficient, unsigned int exponent);
//     unsigned int next_term(unsigned int e) const;
//     unsigned int previous_term(unsigned int e) const;
//     polynomial derivative( ) const;
//     double eval(double x) const;
//     void find_root( double& answer,
//                     bool& success,
//                     unsigned int& iterations,
//                     double guess = 0,
//                     unsigned int maximum_iterations = 100,
//                     double epsilon = 1e-8 ) const;
//     void clear();
//     bool find(const int exp);
   


//     polynomial& operator+=(const Term& t);
//     polynomial& operator*=(const Term& t);
//     polynomial& operator+=(const polynomial& RHS);
//     polynomial& operator*=(const polynomial& RHS);
//     polynomial& operator-=(const polynomial& RHS);
//     polynomial operator-() const;
//     double operator() (double x) const { return eval(x); }


//     friend bool operator==(const polynomial& left, const polynomial& right);
//     friend bool operator!=(const polynomial& left, const polynomial& right);
//     friend polynomial operator+(const polynomial& left, const polynomial& right);
//     friend polynomial operator-(const polynomial& left, const polynomial& right);
//     friend polynomial operator*(const polynomial& left, const polynomial& right);
//     friend polynomial operator/(const polynomial& left, const polynomial& right);
//     friend polynomial operator%(const polynomial& left, const polynomial& right);
//     friend polynomial operator+(const polynomial& left, const Term& t);
//     friend polynomial operator*(const polynomial& left, const Term& t);
//     friend ostream& operator<<(ostream& outs, const polynomial& print_me);
//     friend istream& operator>>(istream& ins, polynomial& read_me);


//     const Term& operator[](const int exp) const;
//     Term& operator[](const int exp);


//     List<Term> list() const;
//     int order() const;
//     double coefficient(unsigned int exponent) const;
//     unsigned int degree( ) const;


// private:
//     List<Term> _poly;
//     int _order;
//     node<Term>* head_ptr;             // Head pointer for list of terms
//     node<Term>* tail_ptr;             // Tail pointer for list of terms
//     mutable node<Term>* recent_ptr;   // Most recently used term
//     void set_recent(unsigned int exponent) const;
// };


#endif
