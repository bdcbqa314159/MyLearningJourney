// testLU.cpp
//
// Testing matrix solvers (LU decomposition)
//
// (C) Datasim Education BV 2003-2004

#include "matrixsolvermechanisms.cpp"
#include "vector.cpp"
#include "doublesweep.cpp"
#include <iostream.h>
#include "arraymechanisms.cpp"

template <class V, class I> void print(const Vector<V,I>& v)
{
	cout << "\n[[Vector: size " << v.Size() << ", Min/Max indices: " << v.MinIndex() << ", " << v.MaxIndex() << endl;

	for (I j = v.MinIndex(); j <= v.MaxIndex(); j++)
	{
		cout << v[j] << ",";
	
	}

	cout << "]]\n";

}

int main()
{
	size_t J = 10;

	// Constructors with size, start index and value (Diagonals of matrix)
	Vector<double, int> a(J-1,	2,	0.0);			// J -1 elements, start index == 2
	Vector<double, int> b(J,	1,	1.0);
	Vector<double, int> c(J-1,	1,	0.0);

	Vector<double, int> r(J, 1, 1.0);				// Right-hand side
	

//	print(a);
//	print(b);
//	print(c);
//	print(r);

	LUTridiagonalSolver<double, int> mysolver(a, b, c, r);
	Vector<double, int> result = mysolver.solve();
	print(result);

/*
	// Constructors with size, start index and value
	Vector<double, int> A(n,	1,	-1.0);
//	print(A); cout << "**";
	Vector<double, int> B(n,	1,	2.0);
	Vector<double, int> C(n,	1,	-1.0);
	Vector<double, int> F(n,	1,	0.0);
	r[1] = 1.0; r[3] = 1.0;

	cout << "Godunov I ...\n";
//	print(A);
//	print(B);
//	print(C);
//	print(F);

	double LHS = 1.0;
	double RHS = 1.0;
	DoubleSweep<double, int> Godunov(A, B, C, F, LHS, RHS);
	Vector<double, int> result2 = Godunov.solve();

	cout << "Godunov II ...\n";
//	print(result2);
*/
	return 0;
}
