#ifndef TEMPLATE_MATRIX_H
#define TEMPLATE_MATRIX_H

#include <iostream>

template<class T>
class Matrix_t
{
public:
    virtual ~Matrix_t();
    virtual T operator()(int i, int j) const = 0;
    virtual T &operator()(int i, int j) = 0;
};

template<class T>
Matrix_t<T>::~Matrix_t(){}

template<class T>
class DenseMatrix_t : public  Matrix_t<T>
{

private:
    int r, c;
    T *d;

public:
    DenseMatrix_t(int nrows, int ncols, T ini = 0);
    virtual ~DenseMatrix_t();
    virtual T operator()(int i, int j) const;
    virtual T& operator()(int i, int j);
};

template<class T>
DenseMatrix_t<T>::~DenseMatrix_t(){
    delete [] d;
}

template<class T>
DenseMatrix_t<T>::DenseMatrix_t(int nrows, int ncols, T ini){
    r = nrows;
    c = ncols;

    d = new T[r*c];
    for (int i = 0; i<r*c; i++)
        d[i] = ini;
}

template<class T>
T DenseMatrix_t<T>::operator()(int i, int j) const{
    return d[i*c+j];
}

template<class T>
T &DenseMatrix_t<T>::operator()(int i, int j){
    return d[i*c+j];
}

void usingTemplateMatrices();

#endif