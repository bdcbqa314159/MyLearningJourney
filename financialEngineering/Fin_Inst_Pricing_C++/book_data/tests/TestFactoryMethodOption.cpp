// TestFactoryMethodOption.cpp
//
// Testing Factory Method pattern
//
// (C) Datasim Education BV 2003
//

#include "eoptionexact.hpp"
#include "executiveoption.hpp"
#include <iostream>


class OptionFactory
{
public:

		virtual Option* createOption() = 0;
};

class MyOptionFactory : public OptionFactory
{
public:

		virtual Option* createOption()
		{
			return new ExactEuropeanOption;
		}
};

class YourOptionFactory : public OptionFactory
{
public:

		virtual Option* createOption()
		{
			return new ExecutiveOption;
		}
};


int main()
{

	cout << "1. European, 2. Executive: ";
	int k;
	cin >> k;

	OptionFactory* of;
	if (k == 1)
		of = new MyOptionFactory;
	else
		of = new YourOptionFactory;


	Option* option = of -> createOption();

	double d = option -> Price();

	cout << "Price is: " << d << endl;


	return 0;
}
