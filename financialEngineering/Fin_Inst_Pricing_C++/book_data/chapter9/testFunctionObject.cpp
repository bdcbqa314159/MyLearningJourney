// testFunctionObject.cpp
//
// Simple tests fro Unary and Binary function objects
//
// (C) Datasim Edcation BV 2003

#include <functional> // needed for function objects
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;	// IMPORTANT


class Greater: public unary_function<int, bool>
{
public:

		result_type operator ()(argument_type k)
		{
			if (k > 10)
				return true;
			else
				return false;
		}
};


template <class Type> class Average : binary_function<Type, Type, Type>
{
public:

		result_type operator ()(first_argument_type a, second_argument_type b)
		{
			return (a + b) * 0.5;
		}
};

int main()
{

	// Iterate in a vector and print numbre of values greater than 10
	vector<int> v1;
	for (int i = 0; i <= 5; i++)
	{
		v1.push_back(5*i);
	}

	// Print the values in the vector
	vector<int>::iterator it;
	for (it = v1.begin(); it != v1.end(); it++)
	{
		cout << (*it) << ", ";
	}

	// Now count number of elements whose value > 10 from start to end
	int result = count_if(v1.begin(), v1.end(), Greater());

	cout << "\nNumber of elements greater than 10: " << result << endl;


	// Now calculate the element-wise averages of vectors v11 and v2 and place
	// them in a vector v3
	vector<double> v11(10, 2.1);	// Size 10, value 2
	vector<double> v2(v11);			// Copy (for convenience, I'm lazy tonight)
	vector<double> v3(v11.size());

	transform(v11.begin(), v11.end(), v2.begin(), v3.begin(), Average<double>());

	cout << "Elements of averaged vector\n";

	vector<double>::iterator itd;

	for (itd = v3.begin(); itd != v3.end(); itd++)
	{
		cout << (*itd) << ", ";
	}


	// We now mutate one element in v2 and test if its elements are pair-wise equal
	// with those of v11
	v2[3] = 4.5;
	vector<double> resultArr(10);
	transform(v2.begin(), v2.end(), v3.begin(), resultArr.begin(), equal_to<double>());

	cout << "\nResult of pairwise comparison \n";
	for (itd = resultArr.begin(); itd != resultArr.end(); itd++)
	{
		cout << (*itd) << ", ";
	}

	cout << endl;


	return 0;
}



