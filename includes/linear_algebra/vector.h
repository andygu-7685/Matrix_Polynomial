#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <sstream>
#include <vector>

template<typename T>
class Vector {
public:
    using value_type = T;

    Vector() = default;
    explicit Vector(size_t n, T value = T()) : _data(n, value) {}

    Vector(std::initializer_list<T> il) : _data(il) {}

    size_t size() const noexcept { return _data.size(); }
    bool empty() const noexcept { return _data.empty(); }

    const T& operator[](size_t i) const { return _data[i]; }
    T& operator[](size_t i) { return _data[i]; }

    const T& at(size_t i) const { return _data.at(i); }
    T& at(size_t i) { return _data.at(i); }

    const T* data() const noexcept { return _data.data(); }
    T* data() noexcept { return _data.data(); }

    void resize(size_t n, T value = T()) { _data.resize(n, value); }
    void clear() noexcept { _data.clear(); }

    T norm2() const {
        T sum = T();
        for (auto& e : _data) {
            sum += e * e;
        }
        return sum;
    }

    double norm() const {
        return std::sqrt(static_cast<double>(norm2()));
    }

    Vector<T> normalized(T eps = T(1e-9)) const {
        double n = norm();
        if (n <= static_cast<double>(eps)) {
            throw std::runtime_error("Vector::normalized: zero-length vector");
        }
        Vector<T> r(size());
        for (size_t i = 0; i < size(); ++i) {
            r[i] = static_cast<T>(_data[i] / n);
        }
        return r;
    }

    T dot(const Vector<T>& other) const {
        if (size() != other.size()) {
            throw std::invalid_argument("Vector::dot: size mismatch");
        }
        T sum = T();
        for (size_t i = 0; i < size(); ++i) {
            sum += _data[i] * other._data[i];
        }
        return sum;
    }

    Vector<T> cross(const Vector<T>& other) const {
        if (size() != 3 || other.size() != 3) {
            throw std::invalid_argument("Vector::cross: both vectors must be size 3");
        }
        return Vector<T>{
            _data[1] * other._data[2] - _data[2] * other._data[1],
            _data[2] * other._data[0] - _data[0] * other._data[2],
            _data[0] * other._data[1] - _data[1] * other._data[0]
        };
    }

    Vector<T>& operator+=(const Vector<T>& rhs) {
        if (size() != rhs.size()) {
            throw std::invalid_argument("Vector::operator+=: size mismatch");
        }
        for (size_t i = 0; i < size(); ++i) _data[i] += rhs._data[i];
        return *this;
    }
    Vector<T>& operator-=(const Vector<T>& rhs) {
        if (size() != rhs.size()) {
            throw std::invalid_argument("Vector::operator-=: size mismatch");
        }
        for (size_t i = 0; i < size(); ++i) _data[i] -= rhs._data[i];
        return *this;
    }

    Vector<T>& operator*=(T scalar) {
        for (auto& x : _data) x *= scalar;
        return *this;
    }

    Vector<T>& operator/=(T scalar) {
        if (scalar == T()) {
            throw std::invalid_argument("Vector::operator/=: divide by zero");
        }
        for (auto& x : _data) x /= scalar;
        return *this;
    }

    friend Vector<T> operator+(Vector<T> a, const Vector<T>& b) { return a += b; }
    friend Vector<T> operator-(Vector<T> a, const Vector<T>& b) { return a -= b; }
    friend Vector<T> operator*(Vector<T> a, T scalar) { return a *= scalar; }
    friend Vector<T> operator*(T scalar, Vector<T> a) { return a *= scalar; }
    friend Vector<T> operator/(Vector<T> a, T scalar) { return a /= scalar; }

    bool operator==(const Vector<T>& rhs) const {
        return _data == rhs._data;
    }

    bool operator!=(const Vector<T>& rhs) const {
        return !(operator==(rhs));
    }

    std::string to_string(int precision = 6) const {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < size(); ++i) {
            oss << std::fixed << std::setprecision(precision) << _data[i];
            if (i + 1 < size()) oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

private:
    std::vector<T> _data;
};

#endif // VECTOR_H