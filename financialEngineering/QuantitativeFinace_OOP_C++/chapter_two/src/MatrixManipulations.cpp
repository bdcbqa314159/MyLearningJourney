#include "chapter_two_lib"

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void MatrixOut(){
    Matrix A(3,4), B(3,4);

    for (int i =0; i<3; i++){
        for (int j = 0; j<4; j++){
            A(i,j) = 0.1*i*j;
            B(i,j) = 1.0 -A(i,j);
        }
    }
    cout<<"Matrix A:"<<endl;
    cout<<A<<endl;
    cout<<"Matrix B:"<<endl;
    cout<<B<<endl;
}

void MatrixModification(){
    Matrix A(3,4), B(3,4);

    for (int i =0; i<3; i++){
        for (int j = 0; j<4; j++){
            A(i,j) = 0.1*i*j;
            B(i,j) = sqrt(1.0 -A(i,j));
        }
    }
    cout<<"Matrix A:"<<endl;
    cout<<A<<endl;
    cout<<"Matrix B:"<<endl;
    cout<<setprecision(12)<<B<<endl;
}