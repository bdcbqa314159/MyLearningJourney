#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "vectors_lib"
#include "matrices_lib"

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

    return 0;
}