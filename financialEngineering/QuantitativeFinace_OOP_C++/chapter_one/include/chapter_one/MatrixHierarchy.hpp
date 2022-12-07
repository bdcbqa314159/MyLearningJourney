#ifndef MATRIX_HIERARCHY_H
#define MATRIX_HIERARCHY_H

#include <iostream>

class Matrix_h
{
public:

    virtual int rows() const = 0;
    virtual int columns() const = 0;
    virtual double operator()(int i, int j) const = 0;
    virtual double &operator()(int i, int j) = 0;
};

class SquareMatrix : public virtual Matrix_h
{

public:
    double determinant() const;
};

class DenseMatrix : public virtual Matrix_h
{

private:
    int r, c;
    double *d;

public:
    DenseMatrix(int nrows, int ncols, double ini = 0.);
    DenseMatrix(const DenseMatrix &mat);
    DenseMatrix(const Matrix_h &mat);
    DenseMatrix &operator=(const Matrix_h &mat);
    inline DenseMatrix &operator=(const DenseMatrix &mat) { return operator=((const Matrix_h &)mat); }

    virtual ~DenseMatrix();
    virtual int rows() const;
    virtual int columns() const;
    virtual double operator()(int i, int j) const;
    virtual double &operator()(int i, int j);
};

class DenseSquareMatrix : public DenseMatrix, public SquareMatrix
{
public:
    inline DenseSquareMatrix(int nrows, double ini = 0.) : DenseMatrix(nrows, nrows, ini){};
};

class DiagonalMatrix : public SquareMatrix
{
private:
    int r;
    double *d;

public:
    DiagonalMatrix(int nrows, double ini = 0.);
    virtual ~DiagonalMatrix();
    virtual int rows() const;
    virtual int columns() const;
    virtual double operator()(int i, int j) const;
    virtual double &operator()(int i, int j);
};

DenseMatrix operator+(const Matrix_h &A, const Matrix_h &B);
std::ostream &operator<<(std::ostream &os, const Matrix_h &A);

void usingMatricesHierarchy();

#endif