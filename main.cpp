#include <iostream>
#include <iomanip>
#include <vector>

#include "includes/poly_list/polynomial.h"

using namespace std;



int main( int argc, char** argv ) {
    //intialize polynomial object
    polynomial p1;
    vector<CoefType> terms1{2, 4, -5, 9};
    p1 = polynomial(terms1);

    //define a square matrix
    initializer_list<initializer_list<double>> list = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<double> x = Matrix<double>(list);
    Matrix<double> y = p1.eval(x);

    cout << y.to_string() << endl;
    return 0;
}