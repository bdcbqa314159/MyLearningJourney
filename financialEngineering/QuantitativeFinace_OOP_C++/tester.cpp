#include <iostream>
#include "chapter_one_lib"

int main()
{
    std::cout << "Working with Erik Schlögl's book!" << std::endl;

    std::cout<<"=============="<<std::endl;
    message();
    std::cout << std::endl;
    different_types();
    std::cout << std::endl;
    switch_example();
    std::cout << std::endl;
    functionCallTest();
    std::cout << std::endl;
    staticVariableTest();
    std::cout << std::endl;
    std::cout<<"=============="<<std::endl;
    usingMatrices();
    std::cout << std::endl;
    std::cout<<"=============="<<std::endl;
    usingMatricesHierarchy();
    std::cout << std::endl;
    std::cout<<"=============="<<std::endl;
    usingTemplateMatrices();

    return 0;
}