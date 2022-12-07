#include "chapter_one_lib"

Matrix::Matrix(int nrows, int ncols, double ini)
{

    r = nrows;
    c = ncols;

    d = new double[nrows * ncols];
    double *p = d;

    for (int i = 0; i < nrows * ncols; i++)
        *p++ = ini;
}

Matrix::Matrix(const Matrix &mat)
{
    r = mat.r;
    c = mat.c;

    d = new double[r * c];
    double *p = d;
    double *pm = mat.d;

    for (int i = 0; i < r * c; i++)
        *p++ = *pm++;
}

Matrix::~Matrix()
{
    delete[] d;
}

Matrix operator+(const Matrix &A, const Matrix &B)
{
    Matrix result(A);
    double *p = result.d;
    double *pB = B.d;

    for (int i = 0; i < A.r * A.c; i++)
        *p++ += *pB++;

    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &A)
{
    int j{};
    for (int i = 0; i < A.rows(); i++)
    {
        for (j = 0; j < A.cols() - 1; j++)
        {
            os << A(i, j) << ",";
        }
        os << A(i, j) << std::endl;
    }
    return os;
}

void usingMatrices()
{
    int i{}, j{};

    Matrix A(3, 2);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            A(i, j) = 0.1 * i * j;
        }
    }

    double sum = 0.;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            sum += A(i, j);
        }
    }

    std::cout << "The Matrix A: " << std::endl;
    std::cout << A << std::endl;
    std::cout << "The sum of the elements in A is " << sum << std::endl;
}