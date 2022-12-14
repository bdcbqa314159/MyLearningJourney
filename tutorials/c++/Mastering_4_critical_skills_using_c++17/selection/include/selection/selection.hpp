#ifndef DECLARING_VARIABLES_H
#define DECLARING_VARIABLES_H

#include <iostream>
#include <string>
#include <vector>

void someTest();

void selection_homework1();
void selection_homework2();
void selection_homework3();
void selection_homework4();
void selection_homework5();
void selection_homework6();

struct Interval
{

    Interval() {}
    Interval(int start, int end) : start(start), end(end) {}
    bool has(int x)
    {
        return (start <= x && x <= end);
    }

    friend std::ostream &operator<<(std::ostream &os, const Interval &original);
    friend bool operator<(const Interval &i1, const Interval &i2);

    int start{}, end{};
};

void selection_homework7();

void selection_homework8();

void testingIntervals();
#endif
