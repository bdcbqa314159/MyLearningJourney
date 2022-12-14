#include <iostream>
#include "vanilla_lib"
#include "monte_carlo_lib"
#include "parameter_lib"

int main()
{
    std::cout << "Working with Joshi's famous book, modern c++ and cmake." << std::endl;

    std::cout << "Chapter four single test : " << std::endl;
    testingVanilla();

    testingSimpleMonteCarlo6();
    testingParameter();
    testingSimpleMonteCarlo7();
}