// testBVP.cpp
//
// Testing BVP mechanisms and related solvers
//
// (C) Datasim Education BV 2001-2003
//

#include "bvpmechanisms.cpp"
#include "BVPsolver.cpp"
#include "range.cpp"
#include <iostream>
#include <math.h>

///////////////////////////////////////////////////////////////////////
template <class V, class I> void print(const Vector<V,I>& v)
{
	cout << "\n[[Vector: size " << v.Size() << ", Min/Max indices: " << v.MinIndex() << ", " << v.MaxIndex() << endl;

	for (I j = v.MinIndex(); j <= v.MaxIndex(); j++)
	{
		cout << v[j] << ",";
	
	}

	cout << "]]\n";

}
/////////////////////////////////////////////////////////////////////////

double a0(const double& x)
{
	return 1.0;
}

double a1(const double& x)
{
	return 0.0;
}

double a2(const double& x)
{
	return 1.0;
}

double f(const double& x)
{
	return x;
}


int main()
{

	Range<double> r(0.0, 3.1415*0.5);
	double bcl = 1.0;
	double bcr = (3.1415*0.5) - 1.0;

	BoundaryValueProblem<double> bvp1(a0, a1, a2, f, r, bcl, bcr);

	BoundaryValueProblemSolver<double, int> bvpSolver(bvp1, 4);

	Vector<double, int> result = bvpSolver.solve();

	print(result);

	double h = 3.1415/20.0;
	double x = h;

	for (int i = 1; i <=10; i++)
	{
		cout << "," << cos(x) - sin(x) + x;
	}

	return 0;
}