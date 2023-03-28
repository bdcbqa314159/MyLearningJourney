// graphicsRepository.hpp
//
// Class that allows us to display values of functions in some
// medium.
//
// This class uses a Visitor for the display functionality. The 
// results are displayed in some medium (that we implement as a 
// Strategy).
//
// (C) Datasim Education BV 2003

#ifndef GraphicsRepository_hpp
#define GraphicsRepository_hpp



#include "range.cpp"
#include "vector.cpp"

#include <string>
using namespace std;



class GraphicsRepositoryVisitor;


class GraphicsRepository
{

private:

	string title;			// The title of the graph
	string hAxis;			// Horizontal axis description
	string vAxis;			// Vertical axis description
	
	int nSteps;				// Number of subdivisions of interval
	Range<double> interval;	// Interval of interest

	double (*f)(double x);	// C style function	

	// Other data
	Vector<double, int> array;	// The array of function values

public:
	GraphicsRepository(double (*fp)(double x), const Range<double>& myRange, int numberSteps = 30);


	// Choosing a new function
	void function(double (*fp)(double x)); 


	void range (const Range<double>& myRange);
	
	string Title() const;
	string XAxisTitle() const;
	string YAxisTitle() const;
	Range<double>& getInterval();
	int numberSteps();
	Vector<double, int> graphValue() const;

	void accept(GraphicsRepositoryVisitor& v);


};



#endif

