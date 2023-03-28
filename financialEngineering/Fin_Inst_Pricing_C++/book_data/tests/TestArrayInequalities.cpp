// TestArrayInequalities.cpp
//
// Test program for vector inequalities
//
// (C) Datasim Education BV 2004
//

#include "arraymechanisms.cpp"


int main()
{
	Vector<double, int> smaller(5, 1);	// Size 5 start index 1
	Vector<double, int> bigger(5, 1);	// Size 5 start index 1

	// Use Spiegel, Schaum Statistics page 113, ex. 5.1 etc.
	smaller[1] = 2.0;
	smaller[2] = 3.0;
	smaller[3] = 7.0;
	smaller[4] = 8.0;
	smaller[5] = 10.0;

	bigger = smaller + 4.0;	// Offset

	if (bigger > smaller) cout << "\nOK1";
	if (bigger >= smaller) cout << "\nOK2";
	if (smaller < bigger) cout << "\nOK3";
	if (smaller <= bigger) cout << "\nOK4";

	if (smaller == bigger) cout << "OOPS";
		else cout << "\nOK5";
	
	if (smaller != bigger) cout << "\nOK6";

	if (positive(smaller) == true)
		cout << "\nOK7";

	smaller -= 100.0;

	if (negative(smaller) == true)
		cout << "\nOK8";

	smaller += 2000.0;

	if (positive(smaller) == true)
		cout << "\nOK9";

	return 0;
}
