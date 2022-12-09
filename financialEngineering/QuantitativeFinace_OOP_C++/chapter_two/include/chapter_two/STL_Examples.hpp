#ifndef STL_EXAMPLES_H
#define STL_EXAMPLES_H
#include <map>

void workingWithVectors();
void workingWithMaps();
void workingWithLists();

template <typename T>
class number_of_occurences {
private:
    std::map<T,int> count_occurences;
public:
    inline void operator()(const T& x) { count_occurences[x]++; };
    inline operator std::map<T,int>&() { return count_occurences; };
};

void workingWithForEach();


#endif