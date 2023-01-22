#include "linear_algebra_lib"
#include <cmath>
#include <vector>
#include <string>

LU_decomposition::LU_decomposition(const Matrix &a) : n(a.row_dimension()), LU(a), a_ref(a), indices(std::vector<int>(n))
{
    const double tiny = 1.e-40;
    double big{}, temp{};
    Vector v(n);
    size_t index_max{};
    d = 1.;

    for (size_t i = 0; i < n; i++)
    {
        big = 0.;
        for (size_t j = 0; j < n; j++)
        {
            temp = abs(LU(i, j));
            if (temp > big)
                big = temp;
        }

        if (big == 0)
            throw std::string{"Singular matrix LU_decomposition"};

        v[i] = 1. / big;
    }

    for (size_t k = 0; k < n; k++)
    {
        big = 0.;
        for (size_t i = k; i < n; i++)
        {
            temp = v[i] * abs(LU(i, k));
            if (temp > big)
            {
                big = temp;
                index_max = i;
            }
        }

        if (k != index_max)
        {
            for (size_t j = 0; j < n; j++)
            {
                temp = LU(index_max, j);
                LU(index_max, j) = LU(k, j);
                LU(k, j) = temp;
            }

            d = -d;
            v[index_max] = v[k];
        }

        indices[k] = index_max;

        if (LU(k, k) == 0.)
            LU(k, k) = tiny;

        for (size_t i = k + 1; i < n; i++)
        {
            LU(i, k) /= LU(k, k);
            temp = LU(i, k);

            for (size_t j = k + 1; j < n; j++)
            {
                LU(i, j) -= temp * LU(k, j);
            }
        }
    }
    return;
}

void LU_decomposition::solve(const Vector &b, Vector &x)
{
    size_t index_1{}, index_2{};
    double sum{};

    if (b.size() != n || x.size() != n)
        throw std::string{"LU_decomposition::solve: bad size"};

    for (size_t i = 0; i < n; i++)
        x[i] = b[i];

    for (size_t i = 0; i < n; i++)
    {
        index_1 = indices[i];
        sum = x[index_1];
        x[index_1] = x[i];

        if (index_2 != 0)
        {
            for (size_t j = index_2 - 1; j < i; j++)
                sum -= LU(i, j) * x[j];
        }

        else if (sum != 0.)
            index_2 = i + 1;

        x[i] = sum;
    }

    for (int i = static_cast<int>(n) - 1; i >= 0; i--)
    {
        sum = x[i];
        for (size_t j = i + 1; j < n; j++)
            sum -= LU(i, j) * x[j];
        x[i] = sum / LU(i, i);
    }
    return;
}

void LU_decomposition::solve(const Matrix &b, Matrix &x)
{
    size_t m = b.column_dimension();

    if (b.row_dimension() != n || x.row_dimension() != n || b.column_dimension() != x.column_dimension())
        throw std::string{"LU_decomposition::solve: bad size"};

    Vector x_temp(n);
    for (size_t j = 0; j < m; j++)
    {
        for (size_t i = 0; i < n; i++)
            x_temp[i] = b(i, j);
        solve(x_temp, x_temp);
        for (size_t i = 0; i < n; i++)
            x(i, j) = x_temp[i];
    }

    return;
}

void LU_decomposition::mProve(const Vector &b, Vector &x)
{
    Vector r(n);

    for (size_t i = 0; i < n; i++)
    {
        long double sdp = -static_cast<long double>(b[i]);
        for (size_t j = 0; j < n; j++)
        {
            sdp += static_cast<long double>(a_ref(i, j)) * static_cast<long double>(x[j]);
        }
        r[i] = static_cast<double>(sdp);
    }

    solve(r, r);
    for (size_t i = 0; i < n; i++)
        x[i] -= r[i];
    return;
}

void LU_decomposition::inverse(Matrix &a_inv)
{
    a_inv.resize(n, n);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
            a_inv(i, j) = 0.;
        a_inv(i, i) = 1.;
    }
    solve(a_inv, a_inv);
    return;
}

double LU_decomposition::determinant()
{
    double d_temp = d;
    for (size_t i = 0; i < n; i++)
        d_temp *= LU(i, i);

    return d;
}