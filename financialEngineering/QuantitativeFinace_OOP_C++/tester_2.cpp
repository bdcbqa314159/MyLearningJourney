#include <iostream>
#include "chapter_two_lib"

int main()
{
    std::cout << "Working with Erik Schlögl's book!" << std::endl;

    MatrixOut();
    std::cout<<"==============="<<std::endl;
    MatrixModification();
    std::cout<<"==============="<<std::endl;
    workingWithVectors();
    std::cout<<"==============="<<std::endl;
    workingWithMaps();
    std::cout<<"==============="<<std::endl;
    workingWithLists();
    std::cout<<"==============="<<std::endl;
    workingWithForEach();

    std::cout<<"*****BOOST*****"<<std::endl;
    workingWithFunctors();
    workingWithBinding_1();
    workingWithBinding_2();
    sharedPointerExample();

    std::cout<<"*****BLITZ*****"<<std::endl;
    firstTest();
    slicing();
    

    return 0;
}