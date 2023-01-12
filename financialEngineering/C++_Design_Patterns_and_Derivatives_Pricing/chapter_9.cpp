#include "solvers_lib"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    std::cout << "Working with Joshi's famous book, modern c++ and cmake." << std::endl;

    std::cout << "Working with solvers here." << std::endl;

    testingBissection();
    testingNewtonRaphson();

    return 0;
}