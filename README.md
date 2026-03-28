
# Polynomial List Double Node Library

A C++ Personal Project that build polynomial arithmetic operations from scratch using doubly-linked list data structure with node-based term storage.

## Overview

This project implements a polynomial class with support for arithmetic operations, evaluation in scalar and square matrix, calculus operations (derivatives) and root finding (Newton's method). Polynomials are represented as sorted doubly-linked lists of terms, where each term consists of a coefficient and exponent.

## Building

- C++11 or later
- CMake 3.14+
- Google Test (GTest) - automatically downloaded by CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Testing
