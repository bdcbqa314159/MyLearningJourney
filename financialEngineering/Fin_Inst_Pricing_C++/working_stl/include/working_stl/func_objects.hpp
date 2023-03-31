#ifndef FUNC_OBJECTS_H
#define FUNC_OBJECTS_H

#include <vector>
#include <functional>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int COMPARE = 10000;

void print(const vector<int> &v);
bool bigger(int i);
bool mycompare(int x, int y);
void testing_func_objects();

#endif