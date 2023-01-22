#ifndef VECTORS_H
#define VECTORS_H
#include <iostream>
#include <vector>

class Vector
{

public:
    Vector() {}

    Vector(size_t dimension) : dimension(dimension), data(std::vector<double>(dimension)) {}

    Vector(size_t dimension, double &value) : dimension(dimension), data(std::vector<double>(dimension, value)) {}

    Vector(const std::vector<double> &data) : dimension(data.size()), data(data) {}

    Vector(const Vector &original) : dimension(original.dimension), data(original.data) {}

    size_t size() const
    {
        return dimension;
    }

    std::vector<double> vector() const
    {
        return data;
    }

    Vector &operator=(const Vector &original);

    void resize(size_t newDimension);
    double const &operator[](size_t index) const;
    double &operator[](size_t index);

    Vector operator-() const;
    double dot(const Vector &vector) const;

    friend Vector operator*(const double &lambda, const Vector &vector);
    friend Vector operator*(const Vector &vector, const double &lambda);
    friend Vector operator+(const Vector &vector_1, const Vector &vector_2);
    friend Vector operator-(const Vector &vector_1, const Vector &vector_2);
    friend double dot(const Vector &vector_1, const Vector &vector_2);

    friend std::ostream &operator<<(std::ostream &os, const Vector &vector);

    ~Vector() {}

private:
    int dimension{};
    std::vector<double> data{};
};

#endif
