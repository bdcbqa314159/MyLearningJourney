// Point.hxx
//
// Basic two dimensional point
//
// (C) Datasim Education BV 1998

#ifndef Point_HXX
#define Point_HXX

#include "common.hxx"

class Point
{ 

private:
	// Data members
	double xc;		// X coordinate
	double yc;		// Y coordinate

public:
	// Constructors and destructor
	Point();							// Default constructor
	Point(double xcs, double ycs);		// Normal constructor with coordinates
	Point(const Point& source);			// Copy constructor
	~Point();							// Destructor

	// Selectors
	double x();							// Get x coordinate
	double y();							// Get x coordinate

	friend ostream& operator << (ostream& os, const Point& p);	// Print point to ostream

	double distance(const Point& p);	// Calculate distance between two points

	// Modifiers
	void x(double xcs);					// Set the x coordinate
	void y(double ycs);					// Set the y coordinate

	// Operators
	Point& operator = (const Point& source);	// Assignment operator
};

#endif	// Point_HXX