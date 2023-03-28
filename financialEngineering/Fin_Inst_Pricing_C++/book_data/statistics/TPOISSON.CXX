// tpoisson.cxx
// Testing the Poisson distribution

#include "poisdist.cxx"
#include <iostream>
using namespace std;


int main()
{

     Poisson<double, int> p(1.2);
     cout << p.expected();

     return 0;
}
