#include "polynomial.h"
bool test_equal(polynomial left, polynomial right) {
    left.remove_zeros();
    right.remove_zeros();
    if(left._order != right._order)
        return false;
    List<Term>::Iterator left_it = left._poly.begin();
    List<Term>::Iterator right_it = right._poly.begin();
    for (; left_it != left._poly.end(); left_it++) {
        if(*left_it != *right_it)
            return false;
        right_it++;
    }
    return true;
}
polynomial::polynomial() {
    _poly = List<Term>(true, true);
    _order = 0;
    head_ptr = nullptr;
    tail_ptr = nullptr;
    recent_ptr = nullptr;
    remove_zeros();
}
polynomial::polynomial(CoefType* term_array, int order) : _order(order), _poly(List<Term>(true, true)) {
    head_ptr = nullptr;
    tail_ptr = nullptr;
    recent_ptr = nullptr;
    for (int i = 0; i < order + 1; i++)
        _poly.insert(Term(term_array[i], i));
    remove_zeros();
}
polynomial::polynomial(const vector<CoefType>& terms) : _order(terms.size() - 1), _poly(List<Term>(true, true)) {
    head_ptr = nullptr;
    tail_ptr = nullptr;
    recent_ptr = nullptr;
    for (int i = 0; i < terms.size(); i++) {
        _poly.insert(Term(terms[i], i));
    }
    remove_zeros();
}
polynomial::polynomial(CoefType c, unsigned int exponent) {
    _poly = List<Term>(true, true);
    _poly.insert(Term(c, exponent));
    _order = exponent;
    head_ptr = _poly.begin().get_ptr();
    tail_ptr = _poly.last_node().get_ptr();
    recent_ptr = nullptr;
    remove_zeros();
}
polynomial::polynomial(const polynomial& source) {
    _poly = List<Term>(true, true);
    _order = source._order;
    head_ptr = nullptr;
    tail_ptr = nullptr;
    recent_ptr = nullptr;
    List<Term>::Iterator it = source._poly.begin();
    while (it != source._poly.end()) {
        _poly.insert(*it);
        it++;
    }
    remove_zeros();
}
polynomial::~polynomial() {
    //cout << "Destroying Poly: " << *this << " (Order: " << _order << ")" << endl;
    _order = 0;
    head_ptr = nullptr;
    tail_ptr = nullptr;
    recent_ptr = nullptr;
}
polynomial& polynomial::operator=(const CoefType& RHS) {
    _poly.clear();
    _poly = List<Term>(true, true);
    _order = 0;
    head_ptr = nullptr;
    tail_ptr = nullptr;
    recent_ptr = nullptr;
    _poly.insert(Term(RHS, 0));
    remove_zeros();
    return *this;
}
polynomial& polynomial::operator=(const polynomial& RHS) {
    if (this == &RHS)
        return *this;
    _poly.clear();
    _poly = List<Term>(true, true);
    _order = RHS._order;
    head_ptr = nullptr;
    tail_ptr = nullptr;
    recent_ptr = nullptr;
    List<Term>::Iterator it = RHS._poly.begin();
    while (it != RHS._poly.end()) {
        _poly.insert(*it);
        it++;
    }
    remove_zeros();
    return *this;
}
void polynomial::remove_zeros() {
    if (_poly.empty()){
        _order = 0;
        _poly.insert(Term(0.0, 0));
        head_ptr = _poly.begin().get_ptr();
        tail_ptr = _poly.last_node().get_ptr();
        recent_ptr = nullptr;
        return;
    }
    else if (_poly.begin()->_coef == 0.0 && _poly.begin()->_exp == 0 && 
             _poly.size() == 1 && _order == 0){
        head_ptr = _poly.begin().get_ptr();
        tail_ptr = _poly.last_node().get_ptr();
        recent_ptr = nullptr;
        return;
    }

    List<Term>::Iterator it = _poly.begin();
    while (it != _poly.end()){
        if (double_equals(it->_coef, 0.0)){
            _poly.Delete(it);
            it = _poly.begin();
        }
        else{
            it++;
        }
    }
    if (!_poly.empty()){
        head_ptr = _poly.begin().get_ptr();
        tail_ptr = _poly.last_node().get_ptr();
        _order = _poly.last_node()->_exp;
    }
    else{
        _order = 0;
        _poly.insert(Term(0.0, 0));
        head_ptr = _poly.begin().get_ptr();
        tail_ptr = _poly.last_node().get_ptr();
        recent_ptr = nullptr;
    }
}
void polynomial::set_recent(unsigned int exponent) const {
    List<Term>::Iterator it = _poly.begin();
    for (; it != _poly.end(); it++){
        if (it->_exp == exponent)
            recent_ptr = it.get_ptr();
    }
}
unsigned int polynomial::next_term(unsigned int e) const {
    List<Term>::Iterator it = _poly.begin();
    for (; it != _poly.end(); it++) {
        if (it->_exp == e) {
            ++it;
            return ((it.is_null()) ? UINT_MAX : it->_exp);
        }
    }
    return UINT_MAX;
}
unsigned int polynomial::previous_term(unsigned int e) const {
    List<Term>::Iterator it = _poly.begin();
    for (; it != _poly.end(); it++) {
        if (it->_exp == e) {
            --it;
            return ((it.is_null()) ? UINT_MAX : it->_exp);
        }
    }
    return UINT_MAX;
}
VarType polynomial::eval(VarType x) const {
    // start with lowest term
    List<Term>::Iterator it = _poly.begin();
    VarType sum = (it != _poly.end()) ? it->_coef * pow(x, it->_exp) : x - x;
    if(it != _poly.end()) ++it;
    for (; it != _poly.end(); it++) {
        sum += it->_coef * pow(x, it->_exp);
    }
    return sum;
}
polynomial polynomial::derivative() const {
    polynomial derive;
    List<Term>::Iterator it;
    for (it = _poly.begin(); it != _poly.end(); it++) {
        if(it->_exp != 0) {
            Term Dterm(it->_coef * it->_exp, it->_exp - 1);
            derive._poly.insert(Dterm);
            derive._order = max(derive._order, it->_exp - 1);
        }
    }
    return derive;
}
void polynomial::find_root(CoefType& answer, bool& success, unsigned int& iterations, CoefType guess, unsigned int maximum_iterations, CoefType epsilon) const {
    // CoefType slope = 0.0;
    // CoefType x;
    // CoefType y;
    // CoefType xInter;
    // for(int i = 0; i < maximum_iterations; i++) {
    //     slope = (this->derivative())(guess);
    //     int ctr = 0;
    //     while(slope == 0.0) {
    //         ctr++;
    //         guess += 1;
    //         slope = (this->derivative())(guess);
    //         if(ctr > 10)
    //             assert(false);
    //     }
    //     x = guess;
    //     y = eval(guess);
    //     xInter = x - (y / slope);
    //     guess = xInter;
    //     if(double_equals(eval(guess), 0.0, epsilon)) {
    //         success = true;
    //         iterations = i + 1;
    //         answer = guess;
    //         return;
    //     }
    // }
    // success = false;
}
void polynomial::add_to_coef(CoefType amount, unsigned int exponent) {
    if(find(exponent)) {
        this->operator[](exponent)._coef += amount;
    }
    else {
        _poly.insert(Term(amount, exponent));
    }
    remove_zeros();
}
void polynomial::assign_coef(CoefType coefficient, unsigned int exponent) {
    if(find(exponent)) {
        this->operator[](exponent)._coef = coefficient;
    }
    else {
        _poly.insert(Term(coefficient, exponent));
    }
    remove_zeros();
}
void polynomial::clear() {
    _poly.clear();
    _order = 0;
    head_ptr = nullptr;
    tail_ptr = nullptr;
    recent_ptr = nullptr;
}
polynomial& polynomial::operator+=(const Term& t) {
    _poly.insert_and_add(t);
    remove_zeros();
    return *this;
}
polynomial& polynomial::operator*=(const Term& t) {
    List<Term>::Iterator it;
    for (it = _poly.begin(); it != _poly.end(); it++)
        *it *= t;
    remove_zeros();
    return *this;
}
polynomial& polynomial::operator+=(const polynomial& RHS) {
    List<Term>::Iterator right;
    for (right = RHS._poly.begin(); right != RHS._poly.end(); right++)
        *this += *right;
    remove_zeros();
    return *this;
}
polynomial& polynomial::operator*=(const polynomial& RHS) {
    List<Term>::Iterator right;
    polynomial product = polynomial();
    for (right = RHS._poly.begin(); right != RHS._poly.end(); right++) {
        polynomial product_portion = (*this) * (*right);
        product += product_portion;
    }
    *this = product;
    return *this;
}
polynomial& polynomial::operator-=(const polynomial& RHS) {
    List<Term>::Iterator right;
    for (right = RHS._poly.begin(); right != RHS._poly.end(); right++)
        *this += -(*right);
    remove_zeros();
    return *this;
}
polynomial polynomial::operator-() const {
    polynomial result = polynomial();
    List<Term>::Iterator src;
    for (src = _poly.begin(); src != _poly.end(); src++)
        result._poly.insert(-(*src));
    return result;
}
bool operator==(const polynomial& left, const polynomial& right) {
    return left._order == right._order;
}
bool operator!=(const polynomial& left, const polynomial& right) {
    return !(left == right);
}
polynomial operator+(const polynomial& left, const polynomial& right) {
    polynomial obj = left;
    obj += right;
    return obj;
}
polynomial operator-(const polynomial& left, const polynomial& right) {
    polynomial obj = left;
    obj -= right;
    return obj;
}
polynomial operator*(const polynomial& left, const polynomial& right) {
    polynomial obj;
    if (right._order == 0 && double_equals(right._poly.begin()->_coef, 0.0) ||
        left._order == 0 && double_equals(left._poly.begin()->_coef , 0.0)) {
        obj._poly.insert(Term(0, 0));  
        return obj;
    }
    obj = left;
    obj *= right;
    return obj;
}
polynomial operator/(const polynomial& left, const polynomial& right) {
    if (right._order > left._order)
        return polynomial();
    if (right._poly.empty() || (right._poly.begin()->_coef == 0.0 && right._poly.last_node()->_exp == 0))
        assert(false && "dividend cannot be 0");
    polynomial leftC = left;
    polynomial rightC = right;
    polynomial quotient = polynomial();
    leftC.remove_zeros();
    rightC.remove_zeros();
    List<Term>::Iterator left_it = leftC._poly.last_node();
    List<Term>::Iterator right_it = rightC._poly.last_node();
    int prev_exp = -100;
    while (!left_it.is_null() && *left_it >= *right_it && !(left_it->_exp == 0 && left_it->_coef == 0.0)) {
        if (!double_equals(left_it->_coef, 0.0)) {
            if(left_it->_exp == prev_exp) {
                //remove the last node
                leftC.assign_coef(0.0, left_it->_exp);
                leftC.remove_zeros();
                left_it = leftC._poly.last_node();
                continue;
            }
            prev_exp = left_it->_exp;

            Term leading_right = *right_it;
            Term leading_left = *left_it;
            Term multiple = leading_left / leading_right;
            quotient._poly.insert(multiple);
            polynomial right_multiple = right * multiple;
            leftC -= right_multiple;
        }
        left_it = leftC._poly.last_node();
    }
    quotient.remove_zeros();
    List<Term>::Iterator quotient_it = quotient._poly.last_node();
    quotient._order = quotient_it->_exp;
    return quotient;
}
polynomial operator%(const polynomial& left, const polynomial& right) {
    polynomial obj;
    polynomial div = left / right;  
    obj = left - (div * right);  
    obj.remove_zeros();
    if (obj._poly.empty()) {
        obj._order = 0;
        obj._poly.insert(Term(0.0, 0));  
        return obj;
    }
    return obj;
}
polynomial operator+(const polynomial& left, const Term& t) {
    polynomial obj = left;
    obj += t;
    return obj;
}
polynomial operator*(const polynomial& left, const Term& t) {
    polynomial obj = left;
    obj *= t;
    return obj;
}
ostream& operator<<(ostream& outs, const polynomial& print_me) {
    print_me._poly.Print();
    return outs;
}
istream& operator>>(istream& ins, polynomial& read_me) {
    List<Term>::Iterator it;
    for (it = read_me._poly.begin(); it != read_me._poly.end(); it++) {
        ins >> *it;  
    }
    return ins;
}
const Term& polynomial::operator[](const int exp) const {
    List<Term>::Iterator it = _poly.begin();
    for (; it != _poly.end(); it++) {
        if (it->_exp == exp) {
            return *it;
        }
    }
    assert(false);  
    return *it;  
}
Term& polynomial::operator[](const int exp) {
    List<Term>::Iterator it = _poly.begin();
    for (; it != _poly.end(); it++) {
        if (it->_exp == exp) {
            return *it;
        }
    }
    assert(false);  
    return *it;  
}
bool polynomial::find(const int exp) {
    List<Term>::Iterator it = _poly.begin();
    for (; it != _poly.end(); it++) {
        if (it->_exp == exp) {
            return true;
        }
    }
    return false;
}
List<Term> polynomial::list() const {
    return _poly;
}
int polynomial::order() const {
    return _order;
}
CoefType polynomial::coefficient(unsigned int exponent) const {
    return this->operator[](exponent)._coef;
}
unsigned int polynomial::degree() const {
    return _order;
}
