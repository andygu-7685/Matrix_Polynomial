#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <vector>
using namespace std;






template<typename T>
class Matrix {
public:
    using value_type = T;

    Matrix() : _rows(0), _cols(0) {}

    Matrix(size_t rows, size_t cols, T value = T())
      : _rows(rows), _cols(cols), _data(rows * cols, value) {}

    Matrix(initializer_list<initializer_list<T>> list) {
        _rows = list.size();
        _cols = _rows ? list.begin()->size() : 0;
        _data.reserve(_rows * _cols);
        for (auto const& row : list) {
            if (row.size() != _cols) {
                throw invalid_argument("Matrix: inconsistent row length");
            }
            _data.insert(_data.end(), row.begin(), row.end());
        }
    }

    //assignment operator
    Matrix<T>& operator=(const Matrix<T>& rhs) {
        _rows = rhs._rows;
        _cols = rhs._cols;
        _data = rhs._data;
        return *this;
    }

    static Matrix<T> identity(size_t n) {
        Matrix<T> I(n, n, T());
        for (size_t i = 0; i < n; ++i) {
            I(i, i) = T(1);
        }
        return I;
    }

    static Matrix<T> zero(size_t rows, size_t cols) {
        return Matrix<T>(rows, cols, T());
    }

    size_t rows() const noexcept { return _rows; }
    size_t cols() const noexcept { return _cols; }

    const T& operator()(size_t r, size_t c) const {
        return _data.at(r * _cols + c);
    }
    T& operator()(size_t r, size_t c) {
        return _data.at(r * _cols + c);
    }

    Matrix<T> transpose() const {
        Matrix<T> Tmat(_cols, _rows);
        for (size_t r = 0; r < _rows; ++r) {
            for (size_t c = 0; c < _cols; ++c) {
                Tmat(c, r) = operator()(r, c);
            }
        }
        return Tmat;
    }



    Matrix<T>& operator+=(const Matrix<T>& rhs) {
        ensure_same_dimensions(rhs);
        for (size_t i = 0; i < _data.size(); ++i) {
            _data[i] += rhs._data[i];
        }
        return *this;
    }

    Matrix<T>& operator+=(const T& scalar) {
        for (size_t i = 0; i < _data.size(); ++i) {
            _data[i] += scalar;
        }
        return *this;
    }

    Matrix<T>& operator-=(const Matrix<T>& rhs) {
        ensure_same_dimensions(rhs);
        for (size_t i = 0; i < _data.size(); ++i) {
            _data[i] -= rhs._data[i];
        }
        return *this;
    }

    Matrix<T>& operator-=(const T& rhs) {
        for (size_t i = 0; i < _data.size(); ++i) {
            _data[i] -= rhs;
        }
        return *this;
    }

    friend Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs) { return lhs += rhs; }
    friend Matrix<T> operator+(Matrix<T> lhs, const T& rhs) { return lhs += rhs; }
    friend Matrix<T> operator+(const T& lhs, Matrix<T> rhs) { return rhs += lhs; }
    friend Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs) { return lhs -= rhs; }
    friend Matrix<T> operator-(Matrix<T> lhs, const T& rhs) { return lhs -= rhs; }
    friend Matrix<T> operator-(const T& lhs, Matrix<T> rhs) { 
        for (size_t i = 0; i < rhs._data.size(); ++i){
            rhs._data[i] = lhs - rhs._data[i];
        }
        return rhs;
    }

    Matrix<T> operator*(const Matrix<T>& rhs)  {
        if (_cols != rhs._rows) {
            throw invalid_argument("Matrix::operator*: incompatible dimensions");
        }
        Matrix<T> result(_rows, rhs._cols, T());
        for (size_t r = 0; r < _rows; ++r) {
            for (size_t c = 0; c < rhs._cols; ++c) {
                T sum = T();
                for (size_t k = 0; k < _cols; ++k) {
                    sum += operator()(r, k) * rhs(k, c);
                }
                result(r, c) = sum;
            }
        }
        return result;
    }

    Matrix<T>& operator*=(const Matrix<T>& rhs) { return *this = *this * rhs; }

    Vector<T> operator*(const Vector<T>& vec) const {
        if (_cols != vec.size()) {
            throw invalid_argument("Matrix::operator*(Vector): dimension mismatch");
        }
        Vector<T> out(_rows);
        for (size_t r = 0; r < _rows; ++r) {
            T sum = T();
            for (size_t c = 0; c < _cols; ++c) {
                sum += operator()(r, c) * vec[c];
            }
            out[r] = sum;
        }
        return out;
    }

    Matrix<T>& operator*=(const T& scalar){
        for (size_t i = 0; i < _data.size(); ++i) {
            _data[i] *= scalar;
        }
        return *this;
    }

    friend Matrix<T> operator*(Matrix<T> lhs, const T& rhs) { return lhs *= rhs; }
    friend Matrix<T> operator*(const T& lhs, Matrix<T> rhs) { return rhs *= lhs; }

    Matrix<T>& operator/=(const T& scalar) {
        for (size_t i = 0; i < _data.size(); ++i) {
            _data[i] /= scalar;
        }
        return *this;
    }

    friend Matrix<T> operator/(Matrix<T> lhs, const T& rhs) { return lhs /= rhs; }

    T determinant() const {
        if (_rows != _cols) {
            throw invalid_argument("Matrix::determinant: must be square");
        }
        size_t n = _rows;
        Matrix<T> temp(*this);
        T det = T(1);

        for (size_t i = 0; i < n; ++i) {
            size_t pivot = i;
            for (size_t r = i; r < n; ++r) {
                if (abs(temp(r, i)) > abs(temp(pivot, i))) {
                    pivot = r;
                }
            }
            if (abs(temp(pivot, i)) <= numeric_limits<T>::epsilon()) {
                return T();
            }
            if (i != pivot) {
                swap_row(temp, i, pivot);
                det = -det;
            }
            det *= temp(i, i);
            for (size_t r = i + 1; r < n; ++r) {
                T factor = temp(r, i) / temp(i, i);
                for (size_t c = i; c < n; ++c) {
                    temp(r, c) -= factor * temp(i, c);
                }
            }
        }
        return det;
    }

    Matrix<T> inverse() const {
        if (_rows != _cols) {
            throw invalid_argument("Matrix::inverse: must be square");
        }
        size_t n = _rows;
        Matrix<T> a(*this);
        Matrix<T> inv = identity(n);

        for (size_t i = 0; i < n; ++i) {
            size_t pivot = i;
            for (size_t r = i; r < n; ++r) {
                if (abs(a(r, i)) > abs(a(pivot, i))) {
                    pivot = r;
                }
            }
            if (abs(a(pivot, i)) <= numeric_limits<T>::epsilon()) {
                throw runtime_error("Matrix::inverse: singular matrix");
            }
            if (i != pivot) {
                swap_row(a, i, pivot);
                swap_row(inv, i, pivot);
            }
            T diag = a(i, i);
            for (size_t c = 0; c < n; ++c) {
                a(i, c) /= diag;
                inv(i, c) /= diag;
            }
            for (size_t r = 0; r < n; ++r) {
                if (r == i) continue;
                T factor = a(r, i);
                for (size_t c = 0; c < n; ++c) {
                    a(r, c) -= factor * a(i, c);
                    inv(r, c) -= factor * inv(i, c);
                }
            }
        }
        return inv;
    }

    bool operator==(const Matrix<T>& rhs) const {
        return _rows == rhs._rows && _cols == rhs._cols && _data == rhs._data;
    }

    bool operator!=(const Matrix<T>& rhs) const {
        return !(*this == rhs);
    }

    string to_string(int precision = 6) const {
        ostringstream oss;
        for (size_t r = 0; r < _rows; ++r) {
            oss << "[";
            for (size_t c = 0; c < _cols; ++c) {
                oss << fixed << setprecision(precision) << operator()(r, c);
                if (c + 1 < _cols) oss << ", ";
            }
            oss << "]";
            if (r + 1 < _rows) oss << "\n";
        }
        return oss.str();
    }

private:
    size_t _rows{0};
    size_t _cols{0};
    vector<T> _data;

    void ensure_same_dimensions(const Matrix<T>& rhs) const {
        if ((_rows != rhs._rows || _cols != rhs._cols)) {
            throw invalid_argument("Matrix: dimension mismatch");
        }
    }

    static void swap_row(Matrix<T>& mat, size_t a, size_t b) {
        if (a == b) return;
        for (size_t c = 0; c < mat._cols; ++c) {
            swap(mat(a, c), mat(b, c));
        }
    }
};









// overload std::pow(matrix, exponent) function
template<typename T>
Matrix<T> pow(const Matrix<T>& m, int exponent) {
    //make sure square matrix
    if (m.rows() != m.cols()) {
        throw invalid_argument("Matrix::pow: matrix must be square");
    }
    if(exponent < 0) {
        throw invalid_argument("Matrix::pow: exponent must be non-negative");
    }
    Matrix<T> result = Matrix<T>::identity(m.rows());
    Matrix<T> temp = m;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = result * temp;
        }
        temp = temp * temp;
        exponent /= 2;
    }
    return result;
}








#endif // MATRIX_H