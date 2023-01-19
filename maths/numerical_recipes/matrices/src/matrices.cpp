#include "vectors_lib"
#include "matrices_lib"

double Matrix::operator()(size_t i, size_t j) const
{
    if (i >= rows || j >= columns)
        throw std::string{"Dimension error"};

    return data[i * columns + j];
}
double &Matrix::operator()(size_t i, size_t j)
{
    if (i >= rows || j >= columns)
        throw std::string{"Dimension error"};

    return data[i * columns + j];
}

size_t Matrix::dim_rows() const
{
    return rows;
}

size_t Matrix::dim_columns() const
{
    return columns;
}

Matrix Matrix::operator-() const
{
    Matrix opposite(rows, columns, 0);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            opposite(i, j) = -operator()(i, j);
        }
    }
    return opposite;
}

Matrix operator*(double lambda, const Matrix &matrix)
{
    Matrix result(matrix);
    for (size_t i = 0; i < matrix.rows; i++)
    {
        for (size_t j = 0; j < matrix.columns; j++)
        {
            result(i, j) = lambda * matrix(i, j);
        }
    }
    return result;
}

Matrix operator*(const Matrix &matrix, double lambda)
{
    return operator*(lambda, matrix);
}

Matrix operator*(const Matrix &matrix_1, const Matrix &matrix_2)
{
    if (matrix_1.columns != matrix_2.rows)
        throw std::string{"Dimension error"};

    size_t common = matrix_1.columns;
    size_t m = matrix_1.rows;
    size_t n = matrix_2.columns;

    Matrix result(m, n, 0);

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            double sum{};
            for (size_t k = 0; k < common; k++)
            {
                sum += matrix_1(i, k) * matrix_2(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

Matrix operator+(const Matrix &matrix_1, const Matrix &matrix_2)
{

    if (matrix_1.columns != matrix_2.columns || matrix_1.rows != matrix_2.rows)
        throw std::string{"Dimension error"};

    size_t m = matrix_1.rows;
    size_t n = matrix_1.columns;

    Matrix result(m, n, 0);

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            result(i, j) = matrix_1(i, j) + matrix_2(i, j);
        }
    }
    return result;
}

Matrix operator-(const Matrix &matrix_1, const Matrix &matrix_2)
{
    return operator+(matrix_1, -matrix_2);
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    size_t m = matrix.rows;
    size_t n = matrix.columns;
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            os << matrix(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}
