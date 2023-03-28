// functionmechanisms.hpp
//
// Common functions that convert standard C functions of 1, 2 and 3
// input variables to fully discrete and semi discrete form. These
// functions are useful when working with FDM because much of the 
// nitty-gritty work is done here and not in the code for the FDM
// schemes (which in itself is difficult enough at the best of times).
// See chapter 9 of Duffy's book.
//
//	Categories:
//
//			f(x), f(t)					Vector
//			f(x, y), f(x, t)			NumericMatrix
//			f(x, y, z), f(x, y, t)		Tensor
//
//	Applications:
//
//			1. Calculating function values (e.g. in FDM schemes)
//			2. Other activities in numerical analysis: divided 
//			differences, numerical integration and so on.
// (C) Datasim Education BV 2003-2004

#ifndef FunctionMechanisms_hpp
#define FunctionMechanisms_hpp

#include "Vector.cpp"
#include "NumericMatrix.cpp"
#include "tensor.cpp"
#include "range.cpp"

// Major group I: Converting function values at discrete points. The 
// result will be a vector, matrix or tensor depending on the number 
// of arguments (the dimension).

// Some remarks:
//	
//	1. All functions are scalar-valued!
//	2. When working with ranges, we take their end-points into consideration
//	when creating vectors and numeric matrices

// GROUP A: Functions of a single variable


Vector<double, int> 
	createDiscreteFunction(double (*f)(double x), const Vector<double, int>& xarr);	

Vector<double, int> 
	createDiscreteFunction(double (*f)(double x), const Range<double>& r, int numSteps);

Vector<double, int> 
	createDiscreteFunction(double (*f)(double x), const Range<double>& r, double h);


// GROUP B: Functions of two variables. Here we have the option of creating 
// a matrix of values in one swoop or to create a vector of values based on 
// a single value of the second variable (the so-called semi-discrete case)

NumericMatrix<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
							const Vector<double, int>& x1Arr, const Vector<double, int>& x2Arr);	
NumericMatrix<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
							const Range<double>& r1, const Range<double>& r2,
							int nSteps1, int nSteps2);	

NumericMatrix<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
							const Range<double>& r1, const Range<double>& r2,
							double h1, double h2);	

// Semi-discrete calculations
Vector<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2), 
			const Vector<double, int>& x1Arr, double x2Val);

// GROUP C: Functions of three variables. In general, the resulting 
// data set would be a Tensor (three-d matrix).

Tensor<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
			const Vector<double, int>& x1Arr, const Vector<double, int>& x2Arr,
			const Vector<double, int>& x3Arr);	

Tensor<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
			const Range<double>& r1, const Range<double>& r2, const Range<double>& r3,
			int nSteps1, int nSteps2, int nSteps3);	

Tensor<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
			const Range<double>& r1, const Range<double>& r2, const Range<double>& r3,
			double h1, double h2, double h3);	


// 'Single' semi-discrete
NumericMatrix<double, int> 
	createDiscreteFunction(double (*f)(double x1, double x2, double x3), 
			const Vector<double, int>& x1Arr, const Vector<double, int>& x2Arr,
			double x3Val);	

#endif