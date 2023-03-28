// TestMatrixInequalities.cpp
//
// Test program for numeric matrix inequalities
//
// (C) Datasim Education BV 2004
//

#include "matrixmechanisms.cpp"


int main()
{
	NumericMatrix<double, int> mat1(5, 5, 1,1);
	NumericMatrix<double, int> mat2(5, 5, 1,1);

	if (mat1 == mat2) 
		cout << "Matrices are equal OKNULL\n";

	for (int j = mat2.MinColumnIndex(); j <= mat2.MaxColumnIndex(); j++)
	{
		for (int i = mat2.MinRowIndex(); i <= mat2.MaxRowIndex(); i++)
		{
			mat2(i,j) = mat1(i,j) + 10.0;
		}
	}

	if (mat2 > mat1) cout << "\nOK1";
	if (mat2 >= mat1) cout << "\nOK2";
	if (mat1 < mat2) cout << "\nOK3";
	if (mat1 <= mat2) cout << "\nOK4";

	if (mat1 == mat2) cout << "OOPS";
		else cout << "\nOK5";
	
	if (mat1 != mat2) cout << "\nOK6";

	if (positive(mat2) == true)
		cout << "\nOK7";


	for (j = mat1.MinColumnIndex(); j <= mat1.MaxColumnIndex(); j++)
	{
		for (int i = mat1.MinRowIndex(); i <= mat1.MaxRowIndex(); i++)
		{
			mat1(i,j) = -10.0;
		}
	}

	print (mat1);

	if (negative(mat1) == true)
		cout << "\nOK8";

	mat2 = -mat1;

	print(mat2);

	if (positive(mat2) == true)
		cout << "\nOK9";

	return 0;
}
