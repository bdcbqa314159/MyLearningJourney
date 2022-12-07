#include "chapter_one_lib"

#include <iostream>

using namespace std;

int add_one_by_value(int x){
    x++;
    return x;
}

int add_one_by_reference(int &x){
    x++;
    return x;
}

int add_one_by_pointer(int* x){
    *x += 1; 
    return *x;
}

void functionCallTest(){
    int y;
    int result;
    
    y = 1;
    result = add_one_by_value(y);
    cout << "After function call by value: " << endl;
    cout << "y is " << y << endl;
    cout << "The function returned " << result << endl << endl;
    
    y = 1;
    result = add_one_by_reference(y);
    cout << "After function call by reference: " << endl;
    cout << "y is " << y << endl;
    cout << "The function returned " << result << endl << endl;
    
    y = 1;
    result = add_one_by_pointer(&y);
    cout << "After function call by pointer: " << endl;
    cout << "y is " << y << endl;
    cout << "The function returned " << result << endl << endl;
}

int static_variable_function(int x){
    static int previous_value;
    int result = previous_value;
    previous_value = x;
    return result;
}

void staticVariableTest(){
    int y;
    int result;
    
    y = 1;
    result = static_variable_function(y);
    cout << "After first function call: " << endl;
    cout << "y is " << y << endl;
    cout << "The function returned " << result << endl << endl;
    
    y = 2;
    result = static_variable_function(y);
    cout << "After second function call: " << endl;
    cout << "y is " << y << endl;
    cout << "The function returned " << result << endl << endl;

    y = 3;
    result = static_variable_function(y);
    cout << "After third function call: " << endl;
    cout << "y is " << y << endl;
    cout << "The function returned " << result << endl << endl;
}