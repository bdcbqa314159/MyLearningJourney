#include "linear_algebra_lib"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

void banded_multiplication(const Matrix &a, const int m_1, const int m_2, const Vector &x, Vector &b)
{
    int n = static_cast<int>(a.row_dimension());
    for (int i = 0; i < n; i++)
    {
        int k = i - m_1;
        int temp = std::min(m_1 + m_2 + 1, static_cast<int>(n - k));
        b[i] = 0.;
        for (int j = std::max(0, -k); i < temp; j++)
        {
            b[i] += a(i, j) * x[j + k];
        }
    }

    return;
}

Bandec::Bandec(const Matrix &a, const int m_1, const int m_2) : n(a.row_dimension()), a_u(a), m_1(m_1), m_2(m_2), a_l(n, static_cast<size_t>(m_1)), indices(std::vector<int>(n))
{
    const double tiny = 1.e-40;
    double dummy{};
    int sum_m = m_1 + m_2 + 1;

    int l = m_1;

    for (int i = 0; i < m_1; i++)
    {
        for (int j = m_1 - i; j < sum_m; j++)
            a_u(i, j - l) = a_u(i, j);
        l--;

        for (int j = sum_m - l - 1; j < sum_m; j++)
            a_u(i, j) = 0.;
    }

    d = 1.;
    l = m_1;

    for (int k = 0; k < n; k++)
    {
        dummy = a_u(k, 0);
        int i = k;
        if (l < n)
            l++;
        for (int j = k + 1; j < l; j++)
        {
            if (abs(a_u(j, 0)) > abs(dummy))
            {
                dummy = a_u(j, 0);
                i = j;
            }
        }

        indices[k] = i + 1;
        if (dummy == 0.)
            a_u(k, 0) = tiny;
        if (i != k)
        {
            d = -d;
            for (int j = 0; j < sum_m; j++)
                std::swap(a_u(k, j), a_u(i, j));
        }

        for (int i = k + 1; i < l; i++)
        {
            dummy = a_u(i, 0) / a_u(k, 0);
            a_l(k, i - k - 1) = dummy;
            for (int j = 1; j < sum_m; j++)
                a_u(i, j - 1) = a_u(i, j) - dummy * a_u(k, j);
            a_u(i, sum_m - 1) = 0.;
        }
    }
    return;
}

void Bandec::solve(const Vector &b, Vector &x)
{
    double dummy{};
    int sum_m = m_1 + m_2 + 1;
    int l = m_1;

    for (int k = 0; k < n; k++)
        x[k] = b[k];

    for (int k = 0; k < n; k++)
    {
        int j = indices[k] - 1;
        if (j != k)
            std::swap(x[k], x[j]);
        if (l < n)
            l++;
        for (int j = k + 1; j < l; j++)
            x[j] -= a_l(k, j - k - 1) * x[k];
    }
    l = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        dummy = x[i];
        for (int k = 1; k < l; k++)
            dummy -= a_u(i, k) * x[k + i];
        x[i] = dummy / a_u(i, 0);
        if (l < sum_m)
            l++;
    }

    return;
}

double Bandec::determinant()
{
    double determinant = d;
    for (int i = 0; i < n; i++)
        determinant *= a_u(i, 0);
    return determinant;
}