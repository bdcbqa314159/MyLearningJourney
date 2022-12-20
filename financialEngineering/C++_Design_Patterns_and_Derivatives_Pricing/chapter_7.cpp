#include <iostream>
#include <vector>
#include "monte_carlo_lib"
#include "path_dependent_lib"
#include "exotic_lib"

using namespace std;

int main()
{
    std::cout << "Working with Joshi's famous book, modern c++ and cmake." << std::endl;
    testingPathDependent();
    testingExotic();
    testingBSEngine();

    return 0;
}