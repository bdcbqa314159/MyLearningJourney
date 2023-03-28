// TestArrayExtremaKurtosis.cpp
//
// Test program for max/min type functions
//
// (C) Datasim Education BV 2004
//

#include "arraymechanisms.cpp"


int main()
{
	Vector<double, int> vec(5, 1);	// Size 5 start index 1

	vec[1] = 2.0;
	vec[2] = 3.0;
	vec[3] = 7.0;
	vec[4] = -88.0;
	vec[5] = 10.0;

	cout << "Maxvalue: " << maxValue(vec) << endl;
	cout << "Minvalue: " << minValue(vec) << endl;

	cout << "Index Maxvalue: " << indexMaxValue(vec) << endl;
	cout << "Index Minvalue: " << indexMinValue(vec) << endl;


	cout << "Max Abs value: " << maxAbsValue(vec) << endl;
	cout << "Min Abs alue: " << minAbsValue(vec) << endl;

	cout << "Index Max Abs value: " << indexMaxAbsValue(vec) << endl;
	cout << "Index Min Abs value: " << indexMinAbsValue(vec) << endl;

	Vector<double, int> vec2(5, 1);	// Size 5 start index 1

	vec2[1] = 2.0;
	vec2[2] = 3.0;
	vec2[3] = 7.0;
	vec2[4] = 0.0;
	vec2[5] = 10.0;

	// vec - vec2
	cout << "Maxvalue: " << maxValue(vec, vec2) << endl;
	cout << "Minvalue: " << minValue(vec, vec2) << endl;

	cout << "Max Abs value: " << maxAbsValue(vec, vec2) << endl;
	cout << "Min Abs alue: " << minAbsValue(vec, vec2) << endl;



	return 0;
}
