#include "vectors_lib"

Vector &Vector::operator=(const Vector &original)
{
    if (this != &original)
    {
        dimension = original.dimension;
        data = original.data;
    }

    return *this;
}

void Vector::resize(size_t newDimension)
{
    dimension = newDimension;
    data.clear();
    data.resize(newDimension);
    return;
}

double const &Vector::operator[](size_t index) const
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

Vector Vector::operator-() const
{
    Vector opposite = *this;
    for (int i = 0; i < dimension; i++)
        opposite[i] = -data[i];
    return opposite;
}

double Vector::dot(const Vector &vector) const
{
    if (dimension != vector.dimension)
        throw std::string{"Dimension error"};
    double result{};
    for (int i = 0; i < dimension; i++)
        result += data[i] * vector[i];
    return result;
}

Vector operator*(const double &lambda, const Vector &vector)
{
    Vector result(vector);
    for (int i = 0; i < vector.size(); i++)
        result[i] *= lambda;
    return result;
}

Vector operator*(const Vector &vector, const double &lambda)
{
    return operator*(lambda, vector);
}

Vector operator+(const Vector &vector_1, const Vector &vector_2)
{
    int dimension_1 = vector_1.size(), dimension_2 = vector_2.size();
    if (dimension_1 != dimension_2)
        throw std::string{"Dimension error"};

    Vector result(dimension_1);
    for (int i = 0; i < dimension_1; i++)
    {
        result[i] = vector_1[i] + vector_2[i];
    }
    return result;
}

Vector operator-(const Vector &vector_1, const Vector &vector_2)
{
    return operator+(vector_1, -vector_2);
}

double dot(const Vector &vector_1, const Vector &vector_2)
{
    int dimension_1 = vector_1.size(), dimension_2 = vector_2.size();
    if (dimension_1 != dimension_2)
        throw std::string{"Dimension error"};
    double result{};

    for (int i = 0; i < dimension_1; i++)
    {
        result += vector_1[i] * vector_2[i];
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Vector &vector)
{
    int dimension = vector.size();
    for (size_t i = 0; i < dimension; i++)
        os << vector[i] << " ";
    return os;
}
