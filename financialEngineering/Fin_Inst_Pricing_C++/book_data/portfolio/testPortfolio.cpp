// testportfolio.cpp
//
// Testing option strategies and portfolios
//
// (C) Datasim Component Technology BV 2004
//

#include "portfolio.hpp"
#include "europeanoption2.hpp"
#include "vector.cpp"
#include "arraymechanisms.cpp"

#include <iostream>

#include "exceldriver.hpp"

void printOneExcel(const Vector<double, int> & x,						
					const Vector<double, int>& functionResult,
					const string& title)
{ 
	// N.B. Excel has a limit of 8 charts; after that you get a run-time error

	cout << "Starting Excel\n";

	ExcelDriver & excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!

	excel.CreateChart(x, functionResult, title, "Stock S", "Profit");

	
}

int main()
{ // All options are European

	// Bull spread

	// Buy a call option
	EuropeanOption futureOption("C");
	futureOption.U = (32.0);
	futureOption.K = (30.0);
	futureOption.T = (0.5);
	futureOption.r = (0.10);
	futureOption.sig = (0.36);
	futureOption.b = ( 0.0);


	// Sell a call option
	EuropeanOption futureOption2("C");
	futureOption2.U = (32.0);
	futureOption2.K = (35.0);
	futureOption2.T = (0.5);
	futureOption2.r = (0.10);
	futureOption2.sig = (0.36);
	futureOption2.b = ( 0.0);

	BullSpread spr1(futureOption, futureOption2);

	double pay = spr1.payoff (32.0);

	cout << "pay off at 32 is: " << pay << endl;

	Range<double> r(20.0, 40.0);
	Vector<double, int> payoffGraph = spr1.payoffGraph(r, 20);
	print(payoffGraph);

	Vector<double, int> x = r.mesh(20);
	printOneExcel(x, payoffGraph, "Bull Spread (Call)");

	return 0;
}
