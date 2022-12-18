#ifndef MATRICES_H
#define MATRICES_H
#include <iostream>
#include <vector>

class Matrix
{
public:
    Matrix() {}

    Matrix(const Matrix &original)
    {
        columns = original.columns;
        rows = original.rows;
        data = original.data;
    }

    Matrix(size_t rows, size_t columns, double value) : rows(rows), columns(columns), data(std::vector<double>(columns * rows, value))
    {
    }

    Matrix(size_t rows, size_t columns, const std::vector<double> &vector) : rows(rows), columns(columns)
    {
        if (rows * columns != vector.size())
            throw std::string{"Error with the dimensions"};

        data = vector;
    }

    ~Matrix() {}

    double operator()(size_t i, size_t j) const;
    double &operator()(size_t i, size_t j);

    size_t dim_rows() const;

    size_t dim_columns() const;

    Matrix operator-() const;

    friend Matrix operator*(double lambda, const Matrix &matrix);
    friend Matrix operator*(const Matrix &matrix, double lambda);
    friend Matrix operator*(const Matrix &matrix_1, const Matrix &matrix_2);
    friend Matrix operator+(const Matrix &matrix_1, const Matrix &matrix_2);
    friend Matrix operator-(const Matrix &matrix_1, const Matrix &matrix_2);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

private:
    size_t columns{}, rows{};
    std::vector<double> data{};
};

#endif