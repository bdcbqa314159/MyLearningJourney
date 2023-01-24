#ifndef BANDED_H
#define BANDED_H

#include <iostream>
#include <vector>
#include "vectors_lib"
#include "matrices_lib"

struct Bandec
{
    size_t n{};
    int m_1{}, m_2{};
    Matrix a_u{}, a_l{};
    std::vector<int> indices;
    double d{};
    Bandec(const Matrix &a, const int m_1, const int m_2);
    void solve(const Vector &b, Vector &x);
    double determinant();
};

void banded_multiplication(const Matrix &a, const int m_1, const int m_2, const Vector &x, Vector &b);

#endif