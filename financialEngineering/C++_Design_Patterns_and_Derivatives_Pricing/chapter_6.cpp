#include <iostream>
#include "monte_carlo_lib"
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
    testingSimpleMonteCarlo9();

    return 0;
}