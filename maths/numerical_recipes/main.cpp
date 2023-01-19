#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "vectors_lib"
// #include "matrices_lib"

using namespace std;

int main()
{
    vector<double> data = {1, 2, 3, 4};

    Vector v(data);

    cout << v << endl;
    cout << -v << endl;

    cout << v - v << endl;

    cout << dot(v, v) << endl;

    return 0;
}