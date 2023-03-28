// tstrandom.cpp
//
// Random number stuff
//
// (C) Datasim Education BV 2003

#include <stdlib.h>
#include <time.h>

#include <iostream.h>

int main()
{
	srand ((unsigned) time (NULL));	// Define seed for random number generator

	cout << "\nFirst bunch\n";

	for (int i = 1; i <= 10; i++)
	{

		cout << double(rand()) / double(RAND_MAX) << ", ";
	}

	cout << "\nNext bunch\n";
	for (i = 1; i <= 10; i++)
	{

		cout << double(rand()) / double(RAND_MAX) << ", ";
	}


	return 0;
}

