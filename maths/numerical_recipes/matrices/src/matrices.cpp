#include "vectors_lib"
#include "matrices_lib"

Matrix &Matrix::operator=(const Matrix &original)
{
    if (this != &original)
    {
        rows = original.rows;
        columns = original.columns;
        data = original.data;
    }

    return *this;
}

double const &Matrix::operator()(size_t i, size_t j) const
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

Matrix Matrix::transpose()
{
    std::vector<double> new_data(data);

    size_t k = 0;
    for (size_t j = 0; j < columns; j++)
    {
        for (size_t i = 0; i < rows; i++)
        {
            new_data[k] = operator()(i, j);
            k++;
        }
    }

    return Matrix(columns, rows, new_data);
}

void Matrix::resize(size_t rows, size_t columns)
{
    this->rows = rows;
    this->columns = columns;
    data.clear();
    data.resize(rows * columns);

    return;
}

Vector Matrix::row(size_t i) const
{
    if (i >= rows)
        throw std::string{"Dimension error"};
    std::vector<double> new_data(columns);

    for (size_t j = 0; j < columns; j++)
    {
        new_data[j] = operator()(i, j);
    }

    return Vector(new_data);
}

Vector Matrix::column(size_t j) const
{
    if (j >= columns)
        throw std::string{"Dimension error"};

    std::vector<double> new_data(rows);
    for (size_t i = 0; i < rows; i++)
    {
        new_data[i] = operator()(i, j);
    }

    return Vector(new_data);
}

Matrix Matrix::operator-() const
{
    std::vector<double> new_data(data);
    for (size_t i = 0; i < rows * columns; i++)
    {
        new_data[i] = -data[i];
    }

    Matrix opposite(rows, columns, new_data);

    return opposite;
}

Matrix operator+(const Matrix &matrix_1, const Matrix &matrix_2)
{
    size_t rows_1 = matrix_1.row_dimension();
    size_t rows_2 = matrix_2.row_dimension();

    size_t columns_1 = matrix_1.column_dimension();
    size_t columns_2 = matrix_2.column_dimension();

    if (rows_1 != rows_2 || columns_1 != columns_2)
        throw std::string{"Dimension error"};

    std::vector<double> data_1 = matrix_1.matrix();
    std::vector<double> data_2 = matrix_2.matrix();

    std::vector<double> data_3(data_1.size());

    for (size_t i = 0; i < data_1.size(); i++)
    {
        data_3[i] = data_1[i] + data_2[i];
    }

    return Matrix(rows_1, columns_1, data_3);
}

Matrix operator-(const Matrix &matrix_1, const Matrix &matrix_2)
{
    return operator+(matrix_1, -matrix_2);
}

Matrix operator*(double lambda, const Matrix &matrix)
{
    std::vector<double> new_data(matrix.matrix());
    for (size_t i = 0; i < matrix.row_dimension() * matrix.column_dimension(); i++)
    {
        new_data[i] = lambda * matrix.matrix()[i];
    }

    Matrix result(new_data);
    return result;
}

Matrix operator*(const Matrix &matrix_1, const Matrix &matrix_2)
{
    size_t rows_1 = matrix_1.row_dimension();
    size_t rows_2 = matrix_2.row_dimension();

    size_t columns_1 = matrix_1.column_dimension();
    size_t columns_2 = matrix_2.column_dimension();

    if (columns_1 != rows_2)
        throw std::string{"Dimension error"};

    Matrix result(rows_1, columns_2);

    for (size_t i = 0; i < rows_1; i++)
    {
        for (size_t j = 0; j < columns_2; j++)
        {
            Vector m_1 = matrix_1.row(i);
            Vector m_2 = matrix_2.column(j);
            result(i, j) = dot(m_1, m_2);
        }
    }
    return result;
}

Vector operator*(const Matrix &matrix, const Vector &vector)
{

    size_t columns = matrix.column_dimension();
    size_t rows = vector.size();

    if (columns != rows)
        throw std::string{"Dimension error"};

    Vector result(columns);
    for (size_t i = 0; i < columns; i++)
    {
        result[i] = dot(matrix.row(i), vector);
    }
    return result;
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
