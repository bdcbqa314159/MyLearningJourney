#include <iostream>
#include "vanilla_lib"
#include "monte_carlo_lib"

int main()
{
    std::cout << "Working with Joshi's famous book, modern c++ and cmake." << std::endl;

    std::cout << "Chapter four single test : " << std::endl;
    testingVanilla();
    testingSimpleMonteCarlo4();
    testingSimpleMonteCarlo5();
    testingSimpleMonteCarlo6();
}