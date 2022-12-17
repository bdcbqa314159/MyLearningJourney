#include "linear_algebra_lib"

Vector operator*(double lambda, const Vector &vector)
{
    size_t dimension = vector.size();
    Vector result(dimension);
    for (size_t i = 0; i < dimension; i++)
    {
        result[i] = lambda * vector[i];
    }

    return result;
}

Vector operator*(const Vector &vector, double lambda)
{
    return operator*(lambda, vector);
}

Vector operator+(const Vector &vector_1, const Vector &vector_2)
{
    size_t dimension_1 = vector_1.dimension, dimension_2 = vector_2.dimension;
    if (dimension_1 != dimension_2)
        throw std::string{"Dimension error"};
    Vector result(dimension_1);
    for (size_t i = 0; i < dimension_1; i++)
        result[i] = vector_1[i] + vector_2[i];
    return result;
}

Vector operator-(const Vector &vector_1, const Vector &vector_2)
{
    return operator+(vector_1, -vector_2);
}

std::ostream &operator<<(std::ostream &os, const Vector &vector)
{
    for (double element : vector.data)
        os << element << " ";
    return os;
}

double Vector::operator[](size_t index) const
{
    if (index >= dimension)
        throw std::string{"Dimension error"};
    return data[index];
}

double &Vector::operator[](size_t index)
{
    if (index >= dimension)
        throw std::string{"Dimension error"};
    return data[index];
}

size_t Vector::size() const
{
    return dimension;
}

Vector Vector::operator-() const
{
    Vector result = *this;
    for (size_t i = 0; i < dimension; i++)
        result[i] = -data[i];
    return result;
}

void Vector::resize(size_t newDimension)
{
    dimension = newDimension;
    data.resize(newDimension);
}