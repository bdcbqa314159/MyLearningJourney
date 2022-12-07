#include "chapter_one_lib"

DenseMatrix::DenseMatrix(int nrows, int ncols, double ini)
{
    r = nrows;
    c = ncols;
    d = new double[nrows * ncols];
    double *p = d;

    for (int i = 0; i < r * c; i++)
        *p++ = ini;
}

DenseMatrix::DenseMatrix(const DenseMatrix &mat)
{
    r = mat.r;
    c = mat.c;

    d = new double[r * c];

    double *p = d;
    double *pm = mat.d;

    for (int i = 0; i < r * c; i++)
        *p++ = *pm++;
}

DenseMatrix::DenseMatrix(const Matrix_h &mat)
{

    r = mat.rows();
    c = mat.columns();
    d = new double[r * c];

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            d[i * c + j] = mat(i, j);
        }
    }
}

DenseMatrix &DenseMatrix::operator=(const Matrix_h &mat)
{
    int j{};
    r = mat.rows();
    c = mat.columns();
    d = new double[r * c];

    for (int i = 0; i < r; i++)
    {
        for (j = 0; j < c - 1; j++)
        {
            d[i * c + j] = mat(i, j);
        }
    }

    return *this;
}

DenseMatrix::~DenseMatrix()
{
    delete[] d;
}

double DenseMatrix::operator()(int i, int j) const
{
    return d[i * c + j];
}

double &DenseMatrix::operator()(int i, int j)
{
    return d[i * c + j];
}

int DenseMatrix::rows() const
{
    return r;
}

int DenseMatrix::columns() const
{
    return c;
}

DenseMatrix operator+(const Matrix_h &A, const Matrix_h &B)
{

    DenseMatrix result(A);
    for (int i = 0; i < A.rows(); i++)
    {
        for (int j = 0; j < A.columns(); j++)
        {
            result(i, j) = A(i, j) + B(i, j);
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix_h &A)
{
    int j{};
    for (int i = 0; i < A.rows(); i++)
    {
        for (j = 0; j < A.columns(); j++)
        {
            os << A(i, j) << ",";
        }
        os << A(i, j) << std::endl;
    }
    return os;
}

DiagonalMatrix::DiagonalMatrix(int nrows, double ini)
{
    r = nrows;
    d = new double[nrows];
    double *p = d;
    for (int i = 0; i < nrows; i++)
        *p++ = ini;
}

DiagonalMatrix::~DiagonalMatrix()
{
    delete[] d;
}

double DiagonalMatrix::operator()(int i, int j) const
{

    return (i == j) ? d[i] : 0.;
}

double &DiagonalMatrix::operator()(int i, int j)
{
    if (i != j)
        throw std::logic_error("Write access to off-diagonal elements of DiagonalMatrix not permitted");
    return d[i];
}

int DiagonalMatrix::rows() const
{
    return r;
}

int DiagonalMatrix::columns() const
{
    return r;
}

void usingMatricesHierarchy()
{
    DenseMatrix A(3, 5), B(3, 5), C(3, 5), D(3, 5);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 5; j++)
            A(i, j) = B(i, j) = C(i, j) = 0.1 * i * j;

    D = A + B + C;

    std::cout << "The matrix D is " << std::endl;
    std::cout << D << std::endl;

    DenseSquareMatrix E(4);
    DiagonalMatrix F(4);

    for (int i = 0; i < 4; i++)
    {
        F(i, i) = -1.5;
        for (int j = 0; j < 4; j++)
            E(i, j) = 1.3 * i + j;
    }

    std::cout << "The sum of E and F is "<<std::endl;
    std::cout << E + F << std::endl;
}