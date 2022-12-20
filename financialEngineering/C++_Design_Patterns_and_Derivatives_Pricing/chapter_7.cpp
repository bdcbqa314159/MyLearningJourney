#include <iostream>
#include "path_dependent_lib"
#include "exotic_lib"
#include <vector>

using namespace std;

int main()
{
    std::cout << "Working with Joshi's famous book, modern c++ and cmake." << std::endl;
    testingPathDependent();
    testingExotic();

    return 0;
}