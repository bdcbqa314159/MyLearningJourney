// tstrandom.cpp
//
// Random number stuff
//

#include <stdlib.h>
#include <time.h>

#include <iostream.h>

int main()
{
	srand ((unsigned) time (NULL));

	for (int i = 1; i <= 10; i++)
	{

		cout << double(rand()) / double(RAND_MAX) << ", ";
	}

	cout << endl << endl;

//	srand ((unsigned) time (NULL));
//	srand (1);						// Sets the starting point for a series of pseudorandom numbers




	srand (1);

	for (i = 1; i <= 10; i++)
	{
		cout << double(rand()) / double(RAND_MAX) << ", ";

	}
	cout << endl << endl;


	srand ((unsigned) time (NULL));

	for (i = 1; i <= 10; i++)
	{

		cout << double(rand()) / double(RAND_MAX) << ", ";
	}

	cout << endl << endl;


	srand (1);

	for (i = 1; i <= 10; i++)
	{
		cout << double(rand()) / double(RAND_MAX) << ", ";

	}
	cout << endl << endl;

	
	srand (100.5363);

	for (i = 1; i <= 10; i++)
	{
		cout << double(rand()) / double(RAND_MAX) << ", ";

	}
	cout << endl << endl;



	srand (546100.5363);

	for (i = 1; i <= 10; i++)
	{
		cout << double(rand()) / double(RAND_MAX) << ", ";

	}
	cout << endl << endl;




	return 0;
}

