#include "linear_algebra_lib"
#include <cmath>
#include <vector>
#include <string>

void gauss_jordan_elimination(Matrix &a, Matrix &b)
{
    int index_col{}, index_row{};
    int rows = static_cast<int>(a.row_dimension()), columns = static_cast<int>(b.column_dimension());

    double big{}, dummy{}, piv_inv{};
    std::vector<int> index_columns(rows), index_rows(rows), index_piv(rows);

    for (int index = 0; index < rows; index++)
    {
        big = 0.;
        for (int j = 0; j < rows; j++)
        {
            if (index_piv[j] != 1)
            {
                for (int k = 0; k < rows; k++)
                {
                    if (index_piv[k] == 0)
                    {
                        if (abs(a(j, k)) >= big)
                        {
                            big = abs(a(j, k));
                            index_row = j;
                            index_col = k;
                        }
                    }
                }
            }
        }
        index_piv[index_col]++;
        if (index_row != index_col)
        {
            for (int m = 0; m < rows; m++)
                std::swap(a(index_row, m), a(index_col, m));
            for (int m = 0; m < columns; m++)
                std::swap(b(index_row, m), b(index_col, m));
        }

        index_rows[index] = index_row;
        index_columns[index] = index_col;

        if (a(index_col, index_col) == 0.)
            throw std::string{"gauss_jordan_elimination: Singular matrix"};
        piv_inv = 1. / a(index_col, index_col);
        a(index_col, index_col) = 1.;

        for (int m = 0; m < rows; m++)
            a(index_col, m) *= piv_inv;
        for (int m = 0; m < columns; m++)
            b(index_col, m) *= piv_inv;

        for (int n = 0; n < rows; n++)
        {
            if (n != index_col)
            {
                dummy = a(n, index_col);
                a(n, index_col) = 0.;

                for (size_t m = 0; m < rows; m++)
                    a(n, m) -= a(index_col, m) * dummy;
                for (size_t m = 0; m < columns; m++)
                    b(n, m) -= b(index_col, m) * dummy;
            }
        }
    }

    for (int m = rows - 1; m >= 0; m--)
    {
        if (index_rows[m] != index_columns[m])
        {
            for (size_t k = 0; k < rows; k++)
                std::swap(a(k, index_rows[m]), a(k, index_columns[m]));
        }
    }

    return;
}

void gauss_jordan_elimination(Matrix &a)
{

    Matrix b(a.row_dimension(), 0);
    gauss_jordan_elimination(a, b);
}
