// functionmechanisms.cpp
//
// Common functions that convert standard C functions of 1, 2 and 3
// input variable to fully discrete and semi-discrete form. These
// functions are useful when working with FDM because much of the 
// nitty-gritty work is done here and not in the code for the FDM
// schemes (which in itself is difficult enough at the best of times).
// See chapter 9 of Duffy's book.
//
// Last modification dates:
//
//	2004-3-9 DD Kick-off code
//	2004-4-6 DD New stuff and testing
//	2004-4-8 DD Code review/testing
//
// (C) Datasim Education BV 2003-2004

#ifndef FunctionMechanisms_cpp
#define FunctionMechanisms_cpp

#include "FunctionMechanisms.hpp"


// Major group I: Converting function values at discrete points. The 
// result will be a vector, matrix or tensor depending on the number 
// of arguments (the dimension).

// N.B. All functions are scalar-valued!

// Functions of a single variable


Vector<double, int> 
	createDiscreteFunction(double (*f)(double x), const Vector<double, int>& xarr)	

{

	Vector<double, int> result(xarr.Size(), xarr.MinIndex());
	

	for (int i = result.MinIndex(); i <= result.MaxIndex(); i++)
	{

		result[i] = (*f)(xarr[i]);
	}

	return result;

}

Vector<double, int> 
	createDiscreteFunction(double (*f)(double), const Range<double>& r, int numSteps)
{

	Vector<double, int> myMesh = r.mesh(numSteps);

	return createDiscreteFunction(f, myMesh);
}


Vector<double, int> 
	createDiscreteFunction(double (*f)(double x), const Range<double>& r, double h)
{
	int nSteps = (r.high() - r.low()) / h;
	
	return createDiscreteFunction(f, r, nSteps);
}

	
// GROUP B: Functions of two variables. Here we have the option of creating a matrix
// of values in one swoop or to create a vector of values based on a single value of 
// the second variable (the so-called semi-discrete case)

NumericMatrix<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
							const Vector<double, int>& x1Arr, const Vector<double, int>& x2Arr)
{

	NumericMatrix<double, int> result(x1Arr.Size(), x2Arr.Size(), 
										x1Arr.MinIndex(), x2Arr.MinIndex());


	for (int i = result.MinRowIndex(); i <= result.MaxRowIndex(); i++)
	{
		
		for (int j = result.MinColumnIndex(); j<= result.MaxColumnIndex(); j++)
		{
				result(i, j) = (*f)(x1Arr[i], x2Arr[j]);
		}

	}

	return result;
}

NumericMatrix<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
							const Range<double>& r1, const Range<double>& r2,
							int nSteps1, int nSteps2)
{

	Vector<double, int> myMesh1 = r1.mesh(nSteps1);
	Vector<double, int> myMesh2 = r2.mesh(nSteps2);

	return createDiscreteFunction(f, myMesh1, myMesh2);

}

NumericMatrix<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
							const Range<double>& r1, const Range<double>& r2,
							double h1, double h2)
{
	int nSteps1 = (r1.high() - r1.low()) / h1;
	int nSteps2 = (r2.high() - r2.low()) / h2;

	return createDiscreteFunction(f, r1, r2, nSteps1, nSteps2);

}


// Semi-discrete calculations
Vector<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
			const Vector<double, int>& x1Arr, double x2Val)
{

	Vector<double, int> result(x1Arr.Size(), x1Arr.MinIndex());


	for (int i = result.MinIndex(); i <= result.MaxIndex(); i++)
	{

		result[i] = (*f)(x1Arr[i], x2Val);
	}

	return result;


}

// GROUP C: Functions of three variables. In general, the resulting data set would 
// be a Tensor (three-d matrix).

Tensor<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
							const Vector<double, int>& x1Arr, const Vector<double, int>& x2Arr,
							const Vector<double, int>& x3Arr)	
{
	Tensor<double, int> result(x1Arr.Size(), x2Arr.Size(), x3Arr.Size(), 
								x1Arr.MinIndex(), x2Arr.MinIndex(), x3Arr.MinIndex());


	for (int k = result.MinThirdIndex(); k <= result.MaxThirdIndex(); k++)
	{

		for (int i = result[k].MinRowIndex(); i <= result[k].MaxRowIndex(); i++)
		{
			for (int j = result[k].MinColumnIndex(); j <= result[k].MaxColumnIndex(); j++)
			{
				result(i, j, k) = (*f)(x1Arr[i], x2Arr[j], x3Arr[k]);
			}
		}
	}


	return result;

}

Tensor<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
			const Range<double>& r1, const Range<double>& r2, const Range<double>& r3,
			int nSteps1, int nSteps2, int nSteps3)
{

	Vector<double, int> myMesh1 = r1.mesh(nSteps1);
	Vector<double, int> myMesh2 = r2.mesh(nSteps2);
	Vector<double, int> myMesh3 = r3.mesh(nSteps3);

	return createDiscreteFunction(f, myMesh1, myMesh2, myMesh3);

}


Tensor<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
			const Range<double>& r1, const Range<double>& r2, const Range<double>& r3,
			double h1, double h2, double h3)
{
	int nSteps1 = (r1.high() - r1.low()) / h1;
	int nSteps2 = (r2.high() - r2.low()) / h2;
	int nSteps3 = (r3.high() - r3.low()) / h3;

	return createDiscreteFunction(f, r1, r2, r3, nSteps1, nSteps2, nSteps3);

}


// 'Single' semi-discrete
NumericMatrix<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
							const Vector<double, int>& x1Arr, const Vector<double, int>& x2Arr,
							double x3Val)
{

	NumericMatrix<double, int> result(x1Arr.Size(), x2Arr.Size(), 
										x1Arr.MinIndex(), x2Arr.MinIndex());


	for (int i = result.MinRowIndex(); i <= result.MaxRowIndex(); i++)
	{
		
		for (int j = result.MinColumnIndex(); j<= result.MaxColumnIndex(); j++)
		{
				result(i, j) = (*f)(x1Arr[i], x2Arr[j], x3Val);
		}

	}

	return result;

}


#endif