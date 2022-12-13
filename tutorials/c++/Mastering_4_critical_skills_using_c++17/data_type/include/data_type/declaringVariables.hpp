#ifndef DECLARING_VARIABLES_H
#define DECLARING_VARIABLES_H

#include <iostream>
#include <string>

void someTest();

void homework_1();

struct student
{
    std::string name;
    int id;
    double grade;

    student(std::string name, int id, double grade) : name(name), id(id), grade(grade) {}

    friend std::ostream &operator<<(std::ostream &os, const student &obj);
};

void homework_2();
void homework_3();

void homework_4();

/*
#include<iostream>
using namespace std;

int main() {
    int num1, num2, num3;

    num1 = 0, num2 = 1, num3 = num1 + num2, cout <<num3<<"\n";
    num1 = num2, num2 = num3, num3 = num1 + num2, cout <<num3<<"\n";
    num1 = num2, num2 = num3, num3 = num1 + num2, cout <<num3<<"\n";
    num1 = num2, num2 = num3, num3 = num1 + num2, cout <<num3<<"\n";
    num1 = num2, num2 = num3, num3 = num1 + num2, cout <<num3<<"\n";
    num1 = num2, num2 = num3, num3 = num1 + num2, cout <<num3<<"\n";
    num1 = num2, num2 = num3, num3 = num1 + num2, cout <<num3<<"\n";
    num1 = num2, num2 = num3, num3 = num1 + num2, cout <<num3<<"\n";
    num1 = num2, num2 = num3, num3 = num1 + num2, cout <<num3<<"\n";

    // https://en.wikipedia.org/wiki/Fibonacci_number

    return 0;
}
Output 1 2 3 5 8 13 21 34 55

*/

void easyProblems();
void homework_4();
void homework_5();
void mediumProblems();

void homework_6();
void homework_7();
void homework_8();

void hardProblems();

#endif
