#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "vectors_lib"
#include "matrices_lib"
#include "linear_algebra_lib"

using namespace std;

void LU_test()
{
    vector<double> data1 = {2, 1, 2, 1, 2, 1, 3, 1, -1};
    vector<double> data2 = {4, 3, 6, 3};

    Matrix A(3, 3, data1);

    LU_decomposition lu(A);

    Matrix A1(2, 2, data2);

    lu.inverse(A1);
    cout << "A1:" << endl;
    cout << A1 << endl;

    vector<double> y = {10, 8, 2};
    Vector y1(y);
    Vector x1 = y1;

    lu.solve(y1, x1);
    cout << "y1:" << endl;
    cout << y1 << endl;

    x1 = y1;

    lu.mProve(y1, x1);
    cout << "x1:" << endl;
    cout << x1 << endl;

    for (int i : lu.indices)
        cout << i << endl;
    cout << "LU in lu:" << endl;
    cout << lu.LU << endl;
}

int main()
{
    vector<double> data = {1, 2, 3, 4};

    Vector v(data);

    cout << v << endl;
    cout << -v << endl;

    cout << v - v << endl;

    cout << dot(v, v) << endl;

    Matrix m(2, 2, data);

    cout << m << endl;

    cout << "++++++" << endl;
    cout << m.column(1) << endl;

    cout << m.row(0) << endl;

    Matrix n(v);
    cout << n << endl;

    vector<double> data_1 = {1, 2, 3, 4, 5, 6};

    Matrix p(2, 3, data_1);

    cout << p << endl;
    p.transpose();

    cout << p << endl;

    vector<double> a = {2, 1, 2, 1, 2, 1, 3, 1, -1};
    vector<double> b = {10, 1, 0, 0, 8, 0, 1, 0, 2, 0, 0, 1};

    Matrix A(3, 3, a);
    Matrix B(3, 4, b);

    cout << "A: " << A << endl;
    cout << "B: " << B << endl;

    gauss_jordan_elimination(A, B);

    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    vector<double> v_solution = {1, 2, 3};
    Vector b_solution(v_solution);
    cout << "solution: " << b_solution << endl;

    cout << "----------------" << endl;
    LU_test();

    return 0;
}