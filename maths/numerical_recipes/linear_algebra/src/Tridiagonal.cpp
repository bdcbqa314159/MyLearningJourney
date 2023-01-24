#include "linear_algebra_lib"
#include <cmath>
#include <vector>
#include <string>

void tridiagonal(const Vector &a, const Vector &b, const Vector &c, const Vector &r, Vector &u)
{
    size_t n = a.size();
    double b_temp = b[0];

    Vector temp(n);
    if (b_temp == 0.)
        throw std::string{"Error with b_temp at 0 in Tridiagonal"};

    u[0] = r[0] / b_temp;

    for (size_t j = 1; j < n; j++)
    {
        temp[j] = c[j - 1] / b_temp;
        b_temp = b[j] - a[j] * temp[j];

        if (b_temp == 0.)
            throw std::string{"Error with b_temp at some j in Tridiagonal"};

        u[j] = (r[j] - a[j] * u[j - 1]) / b_temp;
    }

    for (int j = static_cast<int>(n - 2); j >= 0; j--)
        u[j] -= temp[j + 1] * u[j + 1];

    return;
}