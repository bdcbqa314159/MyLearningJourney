#ifndef LU_DECOMPOSITION_H
#define LU_DECOMPOSITION_H

#include <iostream>
#include <vector>
#include "vectors_lib"
#include "matrices_lib"

struct LU_decomposition
{
    size_t n{};
    Matrix LU;
    std::vector<int> indices;
    double d{};
    const Matrix &a_ref;

    LU_decomposition(const Matrix &a);
    void solve(const Vector &b, Vector &x);
    void solve(const Matrix &b, Matrix &x);
    void inverse(Matrix &a_inv);
    double determinant();
    void mProve(const Vector &b, Vector &x);
};

#endif