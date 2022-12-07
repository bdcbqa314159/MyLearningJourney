#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
private:
    int r, c;
    double *d;

public:
    Matrix(int nrows, int ncols, double ini = 0.);
    Matrix(const Matrix &mat);
    ~Matrix();

    inline int rows() const { return r; };
    inline int cols() const { return c; };

    inline double operator()(int i, int j) const;
    inline double &operator()(int i, int j);

    friend Matrix operator+(const Matrix &A, const Matrix &B);
    friend Matrix operator+(const Matrix &A, double x);
    friend Matrix operator*(const Matrix &A, const Matrix &B);
    friend Matrix operator*(const Matrix &A, double x);
};

std::ostream &operator<<(std::ostream &os, const Matrix &A);
inline double Matrix::operator()(int i, int j) const
{
    return d[i * c + j];
}

inline double &Matrix::operator()(int i, int j)
{
    return d[i * c + j];
}

void usingMatrices();

#endif