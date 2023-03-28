// Main.cpp
//
// Test program for basic shape hierarchy
//
// (C) Datasim Education BV 1998-2004

#include "option.hpp"
//#include "PriceVisitor.hpp"
//#include "CDOPrintVisitor.hpp"
#include "cdo.hpp"

#include <iostream>
using namespace std;

void print(const CDO& sc)
{ // Print the shape composite

	CDO::const_iterator i;

	for (i=sc.Begin(); i!=sc.End(); i++)
	{
		cout<< "Price: " << (*(dynamic_cast<Option*>(*i))).Price()<<", Delta: ";
		cout<< (*(dynamic_cast<Option*>(*i))).Delta()<<"\n";

	}
	cout<<endl<<endl;
}

void main()
{
	// Create a print visitor
	//CDOPrintVisitor print;

	// Create an option
	Option o1;			// Default is a Call
	o1.U = (19.0);
	o1.K = (19.0);
	o1.T = (0.50);
	o1.r = (0.10);
	o1.sig = (0.28);
	o1.b = (0.0);

	Option o2(o1);
	o2.T = 1.0;

	Option o3(o1);
	o2.T = 1.5;

	CDO myCDO;

	// Build Shapecomposite
	myCDO.AddBack(o1.Clone());
	myCDO.AddBack(o2.Clone());
	myCDO.AddBack(o3.Clone());

	print(myCDO);

/*
	print.Visit(o1); cout<<endl;
	print.Visit(o2; cout<<endl;
	print.Visit(o3); cout<<endl;
	print.Visit(myCDO); cout<<endl;



	cout<<endl<<"Translated (-1,-3): "<<endl;
	o11.Accept(print); cout<<endl;
	o2.Accept(print); cout<<endl;
	o3.Accept(print); cout<<endl;
	myCDO.Accept(print); cout<<endl;
	*/
}
