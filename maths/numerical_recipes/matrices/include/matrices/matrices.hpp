#ifndef MATRICES_H
#define MATRICES_H
#include <iostream>
#include <vector>

class Matrix
{

public:
    Matrix() {}
    Matrix(const Matrix &original) : rows(original.rows), columns(original.columns), data(data) {}
    Matrix(size_t rows, size_t columns, std::vector<double> &data)
    {
        if (rows * columns != data.size())
            throw std::string{"Error with the dimensions"};

        this->rows = rows;
        this->columns = columns;
        this->data = data;
    }

    double const &operator()(size_t i, size_t j) const;
    double &operator()(size_t i, size_t j);

    size_t row_dimension() const { return rows; }
    size_t column_dimension() const { return columns; }

    Matrix operator-() const;

    friend Matrix operator+(const Matrix &matrix_1, const Matrix &matrix_2);
    friend Matrix operator-(const Matrix &matrix_1, const Matrix &matrix_2);

    friend Matrix operator*(double &lambda, const Matrix &matrix);
    friend Matrix operator*(const Matrix &matrix_1, const Matrix &matrix_2);

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

    ~Matrix()
    {
    }

private:
    size_t rows{}, columns{};
    std::vector<double> data;
};

#endif