// main.cpp
//
// (C) Datasim Component Technology BV 2003
//
#include "exceldriver.hpp"

#include "doublesweep.cpp"
#include "Vector.cpp"
#include "range.cpp"
#include "Characteristics.hpp"
#include "parabolicpde.cpp"
#include "detfunction.cpp"
#include "ParabolicFDM.cpp"
#include "arraymechanisms.cpp"
#include <list>


#include "FileClass.hpp"

void printOneExcel(const Vector<double, long> & x,						
					const Vector<double, long>& functionResult,
					const string& title)
{ 
	// N.B. Excel has a limit of 8 charts; after that you get a run-time error

	cout << "Starting Excel\n";

	ExcelDriver & excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!

	excel.CreateChart(x, functionResult, title, "X", "Y");

	
}

// Excel output as well
void printInExcel(const Vector<double, long>& x,							// X array
					const list<string>& labels,							// Names of each vector
					const list<Vector<double, long> >& functionResult)	// The list of Y values
{ // Print a list of Vectors in Excel. Each vector is the output of
  // a finite difference scheme for a scalar IVP

	cout << "Starting Excel\n";

	ExcelDriver & excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!


	// Don't make the string names too long!!
	excel.CreateChart(x, labels, functionResult, string("FDM Scalar IVP"),
						string("Time Axis"), string ("Value"));


}


int main()
{
	// Set all ranges
	Range<double> X(Xfrom,Xto);
	Range<double> T(Yfrom,Yto);
	
	// Declare all TwoVarDFunctions
	TwoVarDFunction<double,double,double> Sigma(*sigma);
	TwoVarDFunction<double,double,double> Mu(*mu);
	TwoVarDFunction<double,double,double> Forcing(*forcing);
	TwoVarDFunction<double,double,double> B(*b);
	
	// Declare all AtomicDFunctions
	AtomicDFunction<double,double> Ic(*IC);
	AtomicDFunction<double,double> Bcr(*BCR_Topper_p11);
	AtomicDFunction<double,double> Bcl(*BCL);
	
	// Declare the pde
	ParabolicPDE<double,double,double> pde(X,T,Sigma,Mu,B,Forcing,Ic,Bcl,Bcr);

	// Declare the finite difference scheme
	ParabolicFDM<double,double,double> FDM(pde,XINTERVALS,YINTERVALS,THETA);

	// compute option prices
	FDM.start();
	
	// retrieve and store option prices
	long startIndex = 1;
	Vector <double,long> C_tmp = FDM.line();
	print(C_tmp);
	Vector <double,long> C(XINTERVALS+1,startIndex,0.0);
//	C += C_tmp;
	C = C + C_tmp;

	C[startIndex] = BCL(T.high());
	C[XINTERVALS] = BCR_Topper_p11(T.high());
	
	// make and fill stock price vector
	Vector <double,long> S(XINTERVALS+1,startIndex);
	S[startIndex] = X.low();
	double h = (X.high()-X.low())/XINTERVALS;
	for (long j = S.MinIndex() + 1; j <= S.MaxIndex(); j++)
	{
		S[j] = h + S[j-1];
	}
	
	// make and fill delta vector
	Vector <double,long> Delta(XINTERVALS+1,startIndex);
	long min = Delta.MinIndex();
	long max = Delta.MaxIndex();
	for (j = Delta.MinIndex() + 1; j<Delta.MaxIndex(); j++)
	{
		Delta[j] = (C[j+1] - C[j-1])/(2*h);
	}
	Delta[min] = (C[min+1] - C[min])/h;
	Delta[max] = (C[max] - C[max-1])/h;
	
	// make and fill gamma vector
	Vector <double,long> Gamma(XINTERVALS+1,startIndex);
	for (j = Gamma.MinIndex() + 1; j<Gamma.MaxIndex(); j++)
	{
		Gamma[j] = (Delta[j+1] - Delta[j-1])/(2*h);
	}
	Gamma[min] = (Delta[min+1] - Delta[min])/h;
	Gamma[max] = (Delta[max] - Delta[max-1])/h;
	
	// make result vector
	Vector<Vector<double,long>,long> result(3,startIndex);
	result[1] = C;
	result[2] = Delta;
	result[3] = Gamma;
	
	// write results to file
	FileClass fileclass;
	fileclass.SetFileName("output.dat");
	fileclass.SetAxis(S,result);
	fileclass.WriteToFile();

	// Now Excel output
	list<string> labels;							// Names of each vector
	list<Vector<double, long > > functionResult;	// The list of Y values

	labels.push_back("S");
	labels.push_back("Delta");
	labels.push_back("Gamma");

	functionResult.push_back(C);
	functionResult.push_back(Delta);
	functionResult.push_back(Gamma);

	print (S);
	print (C);

	printOneExcel(S, C, "Price");
	printOneExcel(S, Delta, "Delta");
	printOneExcel(S, Gamma, "Gamma");


	printInExcel(S,labels, functionResult);

	return 0;
}


