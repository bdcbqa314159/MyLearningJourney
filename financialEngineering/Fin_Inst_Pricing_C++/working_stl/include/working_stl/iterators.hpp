#ifndef ITERATORS_H
#define ITERATORS_H

#include <vector>
#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>
#include <numeric>

using namespace std;

vector<double> make_vector(int size);

void print(const vector<double> &v);

void first_test_iterators();

class Point
{
private:
    double xc, yc;

public:
    Point();
    Point(double xc, double yc);
    Point(const Point &source);
    ~Point() {}

    inline double x() { return xc; }
    inline double y() { return yc; }

    friend ostream &operator<<(ostream &os, const Point &p);
    double distance(const Point &p);

    inline void x(double xcs) { xc = xcs; }
    inline void y(double ycs) { yc = ycs; }
    Point &operator=(const Point &source);
};

vector<Point> make_vector_point(int size);

void print(const vector<Point> &v);

void second_test_iterators();

void print(const list<int> &my_list);

void third_test_iterators();

void fourth_test_iterators();

void fifth_test_iterators();
void sixth_test_iterators();
void seventh_test_iterators();

#endif