#include <iostream>
#include "linear_algebra_lib"
#include <vector>

std::ostream &operator<<(std::ostream &os, const std::vector<double> &v)
{
    for (auto x : v)
        os << x << " ";
    return os;
}

using namespace std;

int main()
{
    std::cout << "Working with Joshi's famous book, modern c++ and cmake." << std::endl;

    Vector myTest(3);

    vector<double> v = {1, 3, 4};

    cout << myTest << endl;

    Vector myVec(v);
    cout << myVec << endl;

    cout << -myVec << endl;

    return 0;
}