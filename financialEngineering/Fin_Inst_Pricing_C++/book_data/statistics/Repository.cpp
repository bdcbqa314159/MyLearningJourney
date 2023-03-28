// Repository.cpp
//
// Test program for a repository of singleton distributions
//
// (C) Datasim Education BV 1992-2004

#include "unifdist.cxx"
#include "gammdist.cxx"
#include "expodist.cxx"
#include "miscfun.hxx"
#include "singleton.cpp"

#include <string>
#include <map>
#include <iostream>
using namespace std;

void print(const ContinuousDistribution<double, double>& dis, double x)
{
	cout << "Mean value: " << dis.expected() << " Variance: " << dis.variance() << endl;
	cout << "pdf: " << dis.pdf(x) << " cdf: " << dis.cdf(x) << endl;
}


	
int main()
{
	// Uniform distribution
	Uniform<double> linseg(0.0, 2.0);	// Interval of interest
	print(linseg, 3.0);

	// Gamma distribution
	Gamma<double> g(2.0, 3.9);
	print(g, 3.0);

	// Exponential distribution

	cout << "The exact answer is: " << 1.0/exp(-1.0) << "\n";
	Exponential<double> var1(1.0);
	Exponential<double> var2(2.0);

	print(var1, 3.0);
	print(var2, 3.0);

	Exponential<double>* p = Singleton<Exponential<double> >::instance();

	cout << "Singleton\n";
	print (*p, 4.0);

	Exponential<double> daniel (*p);

	// New  (NON SINGLETON)
	map<string, ContinuousDistribution<double, double>* > myList;
	myList["first"] = &g;
	myList["second"] = &var1;

	cout << "Size of map: " << myList.size() << endl;;

	// Iterating in the map
	map<string, ContinuousDistribution<double, double>* >::iterator i = myList.begin();

	while (i != myList.end())
	{ 
			cout << "Element pair [" << (*i).first << ", mean value: " << (*i).second ->expected() << "]\n";
			i++;
	}

	// New  (SINGLETON)
	map<string, ContinuousDistribution<double, double>* > *  myList2 
		= Singleton<map<string, ContinuousDistribution<double, double>* > >::instance();
 
	(*myList2)["first"] = &g;
	(*myList2)["second"] = &var1;

	cout << "Size of map NUMBER 2: " << (*myList2).size() << endl;;

	i = (*myList2).begin();

	while (i != (*myList2).end())
	{ 
			cout << "Element pair [" << (*i).first << ", mean value: " << (*i).second ->expected() << "]\n";
			i++;
	}

	return 0;

}
