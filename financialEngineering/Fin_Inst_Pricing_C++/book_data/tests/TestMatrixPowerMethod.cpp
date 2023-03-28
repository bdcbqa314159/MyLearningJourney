// TestMatrixPowerMethod.cpp
//
// Test program for the Power method (find the dominant
// eigenvalue of a matrix).
//
// (C) Datasim Education BV 2004
//

#include "matrixmechanisms.cpp"


int main()
{

	size_t J = 30;

	// First test case, trivial solution == 1 (the sanity check)
	// Constructors with size, start index and value (Diagonals of matrix)
	Vector<double, int> a(J-1,	2,	1.0);			// J -1 elements, start index == 2
	Vector<double, int> b(J,	1,	2.0);
	Vector<double, int> c(J-1,	1,	1.0);

	NumericMatrix<double, int> mat = createMatrix(a, b, c);
	Vector<double, int> startVector(mat.Rows(), mat.MinRowIndex(), 2.0);


	Vector<double, int> vec3 = mat * startVector;
//	print(vec3);

//	cout << "\nDominant eigenvalue: " << dominantEigenvalue(mat, startVector, 0.001);

	Vector<double, int> a2(J-1, 2,	-1.0);			// J -1 elements, start index == 2
	Vector<double, int> b2(J,  1,	 2.0);
	Vector<double, int> c2(J-1, 1,	-1.0);
	NumericMatrix<double, int> mat2 = createMatrix(a2, b2, c2);
//	print(mat2);
//	print(startVector);

//	print (mat2);

	cout << "\nDominant eigenvalue: " << dominantEigenvalue(mat2, startVector, 0.001);

	return 0;
}
