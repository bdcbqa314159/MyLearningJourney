#include <iostream>
#include "monte_carlo_lib"
#include "random_lib"

int main()
{
    std::cout << "Working with Joshi's famous book, modern c++ and cmake." << std::endl;
    testingMC();
    testingRandom();

    std::cout << "Chapter one single test : " << std::endl;
    testingSimpleMonteCarlo();
}