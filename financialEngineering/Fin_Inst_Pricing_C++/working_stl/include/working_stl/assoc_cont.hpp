#ifndef ASSOC_CONT_H
#define ASSOC_CONT_H

#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <iterator>

using namespace std;

void working_maps();

template <class T>
void print(const set<T> &mySet, const string &name)
{
    cout << endl
         << name << ", size of set is " << mySet.size() << endl
         << "[";
    typename set<T>::const_iterator i;

    for (i = mySet.begin(); i != mySet.end(); ++i)
    {
        cout << (*i) << ",";
    }

    cout << "]" << endl;
}

void working_sets();
void working_vectors();

#endif