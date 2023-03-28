// testVectorCommandsII.cpp
//
// Testing the Vector operators +, *, -
//
// (C) Datasim Component Technology BV 2004

#include "vector.cpp"
#include "arraymechanisms.cpp"

int main()
{
	Vector<double, int> v(4, 1);	// Size 4, start index 1

	double a = 2.0;
	double b = 1.0;

	assign(v, a);
	print (v);

	Vector<double, int> v2 = v * 2.0;
	Vector<double, int> v3 = 2.0 * v;

	cout << "Scale\n";
	print (v2);
	print (v3);

	cout << "Subtract\n";
	v2 = v - b;
	print (v2);

	cout << "Divide\n";
	v2 = v / a;
	print (v2);

	cout << "Subtract II\n";
	v2 = b - v;
	print (v2);


	return 0;
}
