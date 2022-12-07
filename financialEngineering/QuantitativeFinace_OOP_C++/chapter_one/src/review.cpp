#include "chapter_one_lib"
#include <iostream>

using namespace std;

void message()
{
    /*
    Quick introduction from the book
    */
    // Some boring stuff.
    std::cout << "Hello World!" << std::endl;
}

void different_types()
{
    int i = -3;

    cout << "An integer: " << i << endl;

    double x = 3.5;

    cout << "A double precision floating point number: " << x << endl;

    bool b = true;

    cout << boolalpha;
    cout << "A boolean value: " << b << endl;

    char c = '@';
    cout << "A character: " << c << endl;
}