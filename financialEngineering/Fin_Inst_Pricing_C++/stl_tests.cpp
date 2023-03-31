#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "working_stl_lib"

using namespace std;

int main()
{
     cout << "===in assoc_cont===" << endl;
     working_maps();
     working_sets();
     working_vectors();
     cout << endl
          << endl;
     cout << "===in func_objects===" << endl;
     testing_func_objects();
     cout << endl
          << endl;
     cout << "===in iterators===" << endl;

     first_test_iterators();
     second_test_iterators();
     third_test_iterators();
     fourth_test_iterators();
     fifth_test_iterators();
     sixth_test_iterators();
     seventh_test_iterators();

     return 0;
}