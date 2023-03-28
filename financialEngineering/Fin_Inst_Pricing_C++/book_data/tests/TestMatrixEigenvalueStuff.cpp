//TestMatrixEigenvalueStuff.cpp
//
// Test program for matrix eigenvalues and other useful
// functions in numerical linear algebra.
//
// (C) Datasim Education BV 2004
//

#include "matrixmechanisms.cpp"


int main()
{
	NumericMatrix<double, int> mat1(5, 5, 1,1);
	NumericMatrix<double, int> mat2(5, 5, 1,1);

	size_t J = 2;

	// First test case, trivial solution == 1 (the sanity check)
	// Constructors with size, start index and value (Diagonals of matrix)
	Vector<double, int> a(J-1,	2,	1.0);			// J -1 elements, start index == 2
	Vector<double, int> b(J,	1,	2.0);
	Vector<double, int> c(J-1,	1,	1.0);

	NumericMatrix<double, int> mat = createMatrix(a, b, c);

	print(mat);
	if (diagonallyDominant(mat) == true)
		cout << "Matrix is diagonally dominant\n";

	Vector<double, int> rowsum = sumAbsRow(mat);
	cout << "Row sum: "; print(rowsum);
	Vector<double, int> colsum = sumAbsColumn(mat);
	print(colsum);

	NumericMatrix<double, int> Gershcgorin = eigenvalueBounds(mat);
	print(Gershcgorin);

	int n = mat.Rows();
	double aval = a[a.MinIndex()];
	double bval = b[b.MinIndex()];
	double cval = c[c.MinIndex()];

	// Matrix is Toeplitz so eigenvalues are known
	Vector<double, int> exactEigenvalues (n, mat.MinRowIndex());
	for (int i = exactEigenvalues.MinIndex(); i <= exactEigenvalues.MaxIndex(); i++)
	{

		// Assume real eigenvalues
		exactEigenvalues[i] = bval+ (2.0*sqrt(aval*cval) * cos((double(i) * 3.1415)/(n+1)));
	}

	print(exactEigenvalues);

	// Rayleigh Quotient
	Vector<double, int> vec1 (n, mat.MinRowIndex(), 1.0);
	print (vec1);
	cout << "\nQuadtratic form: " << quadraticForm(mat, vec1) << endl;
	cout << "RayleighQuotient: " << RayleighQuotient(mat, vec1) << endl;

	return 0;
}
