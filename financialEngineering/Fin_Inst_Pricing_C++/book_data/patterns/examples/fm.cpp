// fm.cpp
//
// Using Factory Method pattern
//
// (C) Datasim Education BV 2003

#include <iostream>
using namespace std;

class Product
{
	// Your stuff, you NEED a virtual function her if you us RTTI
	virtual void print() { cout << "A product\n";}

};

class CP1 : public Product
{

	// Your stuff
};

class CP2 : public Product
{

	// Your stuff; 
};


class ProductFactory
{
public:
	
	virtual Product* createProduct() = 0;

};

class MyProductFactory : public ProductFactory
{

public:
	Product* createProduct() {cout << "CP1 just made\n"; return new CP1;}

};

class YourProductFactory : public ProductFactory
{

public:
	Product* createProduct() {cout << "CP2 just made\n"; return new CP2;}

};

////////////////////////////////// Abstarct Factory interfaces ///////////////////////////
class AbstractProductFactory
{ // One particular interface for use in Abstract Factory pattern
public:
	
	virtual Product* createCP1() = 0;
	virtual Product* createCP2() = 0;


};

class AbstractProductFactory2
{ // One particular interface for use in Abstract Factory pattern
public:
	
	virtual CP1* createCP1() = 0;
	virtual CP2* createCP2() = 0;


};

class MyConfigurator: public AbstractProductFactory
{ // One particular interface for use in Abstract Factory pattern
public:
	
	Product* createCP1() { return new CP1; }
	Product* createCP2() { return new CP2; }


};

class MyConfigurator2: public AbstractProductFactory2
{ // One particular interface for use in Abstract Factory pattern
public:
	
	CP1* createCP1() { return new CP1; }
	CP2* createCP2() { return new CP2; }


};
ProductFactory* getFactory()
{
	cout << "1. My Factory, 2. Your factory: " << endl;

	int k; cin >> k;

	if (k == 1)
		return new MyProductFactory;

	if (k == 2)
		return new YourProductFactory;

	// Default
		return new MyProductFactory;

}

int main()
{
	// Factory method stuff
	ProductFactory* currentFactory = getFactory();

	Product* myProduct = currentFactory -> createProduct();

	delete myProduct;

	// Abstract Factory stuff, alternative 1
	AbstractProductFactory* myF = new MyConfigurator;

	CP1* cp1; CP2* cp2;

	Product* prodA = myF -> createCP1();
	Product* prodB = myF -> createCP2();

	cp1=dynamic_cast<CP1*>(prodA);
	if (cp1!=0)
	{
			cout << "OK, RTTI works, this is a CP1 thing\n";
	}

	delete prodA;
	delete prodB;

	// Abstract Factory stuff, alternative 1
	AbstractProductFactory2* myF2 = new MyConfigurator2;

	
	CP1* prodA2 = myF2 -> createCP1();
	CP2* prodB2 = myF2 -> createCP2();

	
	delete prodA2;
	delete prodB2;

	return 0;
}

