// testPropertyCommand2.cpp
//
// EXX. 1. Operator overloading
//
//	2002-12-28 DD Main use is in testing properties and commands
//
// (C) Datasim Education BV 2001-2003
//


#include "propertycommand.cpp"
#include <iostream>
#include <string>

using namespace std;

typedef Property<string, bool> BooleanProperty;
typedef SimplePropertySet<string, bool> BooleanPropertySet;
typedef Property<string, bool> BP;
typedef SimplePropertySet<string, bool> BPS;

BooleanProperty NOT(const BooleanProperty& A)
{
	
	BooleanProperty result (A);		// Prototype
	if (A() == false)
	{
		result(true);
	}
	else
	{
		result(false);
	}

	return result;
}

BooleanProperty operator !(const BooleanProperty& A)
{
	return NOT(A);
}

BooleanProperty AND(const BooleanProperty& A, const BooleanProperty& B)
{
	
	BooleanProperty result ("[" + A.name() + " And " + B.name() + "]");		// Prototype

	result(false);

	if (A() == true)
	{
		if (B() == true)
			result(true);
	}

	return result;
}

BooleanProperty AND(const BooleanPropertySet& set)
{ // Modelling Logic Circuits (and-gates)
	
	BooleanProperty result ("[And of a set]", false);		// Prototype

	// One false value and we are finished

	// We iterate over the list until we find the value
	BooleanPropertySet::const_iterator it;

	for (it=set.Begin(); it!=set.End(); it++)
	{ 
		
		if ((*it)() == false)
		{
			return result;
		}
	}

	result(true);

	return result;
}

BooleanProperty operator & (const BooleanProperty& A, const BooleanProperty& B)
{

	return AND(A, B);
}

BooleanProperty operator & (const BooleanProperty& A, const BooleanPropertySet& B)
{

	return A & AND(B);
}

BooleanProperty operator & (const BooleanPropertySet& A, const BooleanProperty& B)
{

	return B & A;
}



BooleanProperty INCLUSIVEOR(const BooleanProperty& A, const BooleanProperty& B)
{
	
	BooleanProperty result ("[" + A.name() + " Inclusive OR " + B.name() + "]");		// Prototype

	result(true);

	if (A() == false)
	{
		if (B() == false)
			result(false);
	}

	return result;
}

BooleanProperty INCLUSIVEOR(const BooleanPropertySet& set)
{ //Modelling Logic Circuits (or-gates)
	
	BooleanProperty result ("[Inclusive or a set]", false);		// Prototype


	// We iterate over the list until we find the value
	BooleanPropertySet::const_iterator it;

	for (it=set.Begin(); it!=set.End(); it++)
	{ 
		
		if ((*it)() == true)
		{
			return result;
		}
	}

	return result;
}

BooleanProperty OR(const BooleanProperty& A, const BooleanProperty& B)
{
	return INCLUSIVEOR(A, B);
}

BooleanProperty operator ||(const BooleanProperty& A, const BooleanProperty& B)
{

	return INCLUSIVEOR(A, B);
}

BooleanProperty operator || (const BooleanProperty& A, const BooleanPropertySet& B)
{

	return OR(A, INCLUSIVEOR(B));
}

BooleanProperty operator || (const BooleanPropertySet& A, const BooleanProperty& B)
{

	return B || A;
}

BooleanProperty operator || (const BooleanPropertySet& A, const BooleanPropertySet& B)
{

	return A || INCLUSIVEOR(B) ;
}


BooleanProperty EXCLUSIVEOR(const BooleanProperty& A, const BooleanProperty& B)
{
	
	BooleanProperty result ("[" + A.name() + " Exclusive OR " + B.name() + "]");		// Prototype

	result(false);

	if (A() == B())
	{
		result(true);
	}

	return result;
}

BooleanProperty XOR(const BooleanProperty& A, const BooleanProperty& B)
{
	return EXCLUSIVEOR(A, B);
}

BooleanProperty operator +(const BooleanProperty& A, const BooleanProperty& B)
{

	return EXCLUSIVEOR(A, B);
}


BooleanProperty IMPLIES(const BooleanProperty& A, const BooleanProperty& B)
{
	BooleanProperty result ("[" + A.name() + " Implies " + B.name() + "]");		// Prototype

	result(true);

	if (A() == true)
	{
		if (B() == false)
			result(false);
	}
	return result;
}

BooleanProperty operator ^(const BooleanProperty& A, const BooleanProperty& B)
{

	return IMPLIES(A, B);
}


BooleanProperty BICONDITIONAL(const BooleanProperty& A, const BooleanProperty& B)
{
	BooleanProperty result ("[" + A.name() + " Biconditional " + B.name() + "]");		// Prototype

	result(true);

	if (A() == true)
	{
		if (B() == false)
			result(false);
	}
	return result;
}

BooleanProperty operator %(const BooleanProperty& A, const BooleanProperty& B)
{

	return BICONDITIONAL(A, B);
}



//////////////////////////////////////////////////////////////////
void print (BooleanProperty& bp)
{
	string ans = "false";
	if (bp() == true)
	{
		ans = "true";
	}

	cout << "Name of boolean: " << bp.name() << ", Value: " << ans << endl;
}

///////////////////////////////////////////////////////////////////

int main()
{

	// Not
	BooleanProperty myProp1 ("A", false);
	BooleanProperty myPropNOT = NOT(myProp1);
	print(myPropNOT);
	print(!myProp1);

	// AND
	BooleanProperty myProp2 ("A", true);
	BooleanProperty myProp3 ("B", true);

	BooleanProperty myPropAND = AND(myProp2, myProp3);
	print(myPropAND);
	print(myProp2 & myProp3);

	// Schaum page 6
	cout << "Concatenated stuff\n";
	BP A(true), B(true), C(true);
	BP answer = A || (B & C); 
	print (answer);						// T

	BP A1(false), B1(true), C1(true);
	BP answer1 = A1 || (B1 & C1); 
	print (answer1);					// T

	BP A2(false), B2(false), C2(false);
	BP answer2 = A2 || (B2 & C2); 
	print (answer2);					// F

	// Conditional
	cout << "Conditional\n";
	answer = (A || (B & C)) ^ B;		// T
	print(answer);

	answer1 = (A1 || (B1 & C1)) ^ B1;	// T
	print(answer1);

	answer2 = (A2 || (B2 & C2)) ^ B2;	// T
	print(answer2);

	// AND of a property set
	cout << "Sets\n";
	BPS bs;
	bs.add(A);
	bs.add(!A);
	bs.add(B&C);

	BP myresult = AND(bs);
	print(myresult);

	BPS bs1;
	bs1.add(A1);
	bs1.add(!A1);
	bs1.add(B1&C1);

	bs1.add(bs);

	myresult = AND(bs1);
	myresult.name(string("My second Double set "));
	print (myresult);
	cout << "Size of double set: " << bs1.Count() << endl;

	// Now for a big one
	BP result = (bs || bs1) & bs & A1 || B1;
	print(result);

	return 0;
}
