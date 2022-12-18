#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "vectors_lib"
#include "matrices_lib"

using namespace std;

int main()
{
    vector<double> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    Matrix testMatrix(3, 4, data);

    cout << testMatrix << endl;

    try
    {
        cout << testMatrix(5, 5) << endl;
    }

    catch (string &error)
    {
        cerr << "Problem: " << error << endl;
    }

    return 0;
}