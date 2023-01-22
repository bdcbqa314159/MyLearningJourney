#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "vectors_lib"
#include "matrices_lib"
#include "linear_algebra_lib"

using namespace std;

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

    return 0;
}