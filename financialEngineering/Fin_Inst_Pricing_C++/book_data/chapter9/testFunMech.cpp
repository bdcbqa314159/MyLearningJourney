// testFunMech.cpp
//
// Testing function mechanisms. This is a
// 'get it working' example to test the code and
// so on.
//
// (C) Datasim Education BV 2003-2004

#include "functionmechanisms.cpp"
#include "arraymechanisms.cpp"
#include "matrixmechanisms.cpp"

template <class V, class I> void print (Tensor<V, I>& tensor)
{
	cout << "Tensor, Rows " << tensor.Rows() << ", Columns " << tensor.Columns() << 
			", Third Dimension " << tensor.sizeThird() << endl;

	for (long k = tensor.MinThirdIndex(); k<= tensor.MaxThirdIndex(); k++)
	{
		print (tensor[k]);
	}
}

double func1(double x)
{
	return x;
}

double func2(double x1, double x2)
{
	return x1 + x2;
}

double func3(double x1, double x2, double x3)
{
	return 0;//x1*x2*x3;
}

int main()
{
	// Functions of 1 variable

	Vector<double, int> Xarr(5);	// Length 5, start index == 1
	Xarr[1] = 0.0; 
	Xarr[2] = 0.25; 
	Xarr[3] = 0.5; 
	Xarr[4] = 0.75; 
	Xarr[5] = 1.0; 

	Vector<double, int> Yarr = createDiscreteFunction(func1, Xarr);

	print(Yarr);

	Range<double> range(0.0, 1.0);
	int N = 4;
	Vector<double, int> Yarr2 = createDiscreteFunction(func1, range, N);
	print(Yarr2);

	double h = (range.high() - range.low() ) / double(N);
	cout << "\nMesh size is " << h << endl;

	Vector<double, int> Yarr3 = createDiscreteFunction(func1, range, h);
	print(Yarr3);


	// Functions of 2 variables
	Range<double> r1(0.0, 1.0);
	Range<double> r2(0.0, 1.0);
	Range<double> r3(0.0, 1.0);

	double h1 = 0.25; double h2 = 0.25; double h3 = 0.5;
	int nSteps1 = 4; int nSteps2 = 4; int nSteps3 = 2;

	Vector<double, int> X(Xarr);
	Vector<double, int> Y(Xarr);
	Vector<double, int> Z(Xarr);


	NumericMatrix<double, int> mat1 = 
					createDiscreteFunction(func2, X, Y);	
	print(mat1);

	NumericMatrix<double, int> mat2 = 
				createDiscreteFunction(func2, r1, r2, nSteps1, nSteps2);	
	print(mat2);

	mat2 = 	createDiscreteFunction(func2, r1, r2, h1, h2);	
	print(mat2);

	// Semi-discrete calculations
	double x2Val = 2.0;
	Vector<double, int> vec = 
			createDiscreteFunction(func2, X, x2Val);

	print(vec);

	// Functions of 3 variables
	Tensor<double, int> tensor = 
					createDiscreteFunction(func3, X, Y, Z);
	print(tensor);

	Tensor<double, int> tensor2 = 
					createDiscreteFunction(func3, r1, r2, r3,
											nSteps1, nSteps2, nSteps3);
	print(tensor2);

	Tensor<double, int> tensor3 = 
					createDiscreteFunction(func3,r1, r2, r3, h1, h2, h3);
	print(tensor3);

	double zval = 9.0;
	NumericMatrix<double, int> sd = 
		createDiscreteFunction(func3, X, Y, zval);

	print (sd);

	return 0;
}
