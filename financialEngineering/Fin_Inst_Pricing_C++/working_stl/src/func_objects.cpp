#include "working_stl_lib"

using namespace std;

void print(const vector<int> &v)
{
    vector<int>::const_iterator i;
    for (i = v.begin(); i != v.end(); ++i)
        cout << *i << ",";
    cout << endl
         << endl;
}

bool bigger(int i)
{
    greater<int> g;
    return g(i, COMPARE);
}

bool mycompare(int x, int y)
{
    if (x % 2 == y % 2)
        return x < y;
    if (x % 2 == 1)
        return true;
    return false;
}

void testing_func_objects()
{
    vector<int> v1;
    for (int i = 0; i < 10; ++i)
        v1.push_back(rand());

    cout << "Random list" << endl;
    print(v1);

    int i = count_if(v1.begin(), v1.end(), bigger);
    cout << "Using bigger function" << endl;
    cout << "there are " << i << " elements greater than " << COMPARE << endl
         << endl;

    i = count_if(v1.begin(), v1.end(), bind(greater<int>(), placeholders::_1, COMPARE));

    cout << "Using bind2nd function adapter" << endl;
    cout << "there are " << i << " elemenst greater than " << COMPARE << endl
         << endl;

    cout << "Sort the list using my compare function" << endl;
    cout << "first all odd numbers from low to high, then all even numbers from low to high" << endl;
    sort(v1.begin(), v1.end(), mycompare);
    print(v1);

    vector<int> v2(v1.size());
    cout << endl
         << "Transform the list using the negate function as argument" << endl;
    transform(v1.begin(), v1.end(), v2.begin(), negate<int>());
    print(v2);
}