#ifndef ARRAYS_H
#define ARRAYS_H
#include <iostream>
#include <vector>

class Vector
{

public:
    Vector() {}

    Vector(const Vector &original)
    {
        dimension = original.dimension;
        data = original.data;
    }

    Vector(const std::vector<double> &vector) : data(vector), dimension(vector.size())
    {
    }

    Vector(size_t dimension) : dimension(dimension), data(std::vector<double>(dimension))
    {
    }

    ~Vector() {}

    double operator[](size_t index) const;

    double &operator[](size_t index);

    size_t size() const;

    void resize(size_t newDimension);

    Vector operator-() const;

    friend Vector operator*(double lambda, const Vector &vector);
    friend Vector operator*(const Vector &vector, double lambda);
    friend Vector operator+(const Vector &vector_1, const Vector &vector_2);
    friend Vector operator-(const Vector &vector_1, const Vector &vector_2);
    friend std::ostream &operator<<(std::ostream &os, const Vector &vector);

private:
    size_t dimension{};
    std::vector<double> data{};
};

#endif