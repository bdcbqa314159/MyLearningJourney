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

void switch_example(){

    int c{};
    cout<<"Enter an integer between 1 and 7: "<<endl;
    cin>>c;

    switch(c){
        case 1: cout<<"Sunday"<<endl;
        break;

        case 2: cout<<"Monday"<<endl;
        break;

        case 3: cout<<"Tuesday"<<endl;
        break;

        case 4: cout<<"Wednesday"<<endl;
        break;

        case 5: cout<<"Thursday"<<endl;
        break;

        case 6: cout<<"Friday"<<endl;
        break;

        case 7:cout<<"Saturday"<<endl;
        break;

        default: cout<<"Invalid input"<<endl;
        break;
    }

}