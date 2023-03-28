// Point.cxx
//
// Basic two dimensional point
//
// (C) Datasim Education BV 1998

#include "Point.hxx"
#include <math.h>

// Constructors
Point::Point()
{ // Default constructor

	xc=yc=0.0;
}

Point::Point(double xcs, double ycs)
{ // Constructor with x- and y-coordinates

	xc=xcs;
	yc=ycs;
}

Point::Point(const Point& source)
{ // Copy constructor

	xc=source.xc;
	yc=source.yc;
}

Point::~Point()
{ // Destructor

//	cout << "point goes away\n";
}

// Selectors
double Point::x() const
{ // Return the x coordinate

	return xc;
}

double Point::y() const
{ // Return the y coordinate

	return yc;
}

bool Point::operator == (const Point& pt) const
{ // Are two points equal?

	if (xc == pt.xc && yc == pt.yc)
			return true;
	return false;
}

bool Point::operator < (const Point& pt) const
{ // Smaller point?

	if (xc < pt.xc && yc < pt.yc)
			return true;
	return false;
}

ostream& operator << (ostream& os, const Point& p)
{ // Print to point to ostream 

	os<< "("<<p.xc<<", "<<p.yc<<")";
	return os;
}

double Point::distance(const Point& p)
{ // Calculate the distance to a point

	double dx=xc-p.xc;
	double dy=yc-p.yc;

	return sqrt(dx*dx+dy*dy);
}


// Modifiers
void Point::x(double xcs)
{ // Set the x coordinate

	xc=xcs;
}

void Point::y(double ycs)
{ // Set the y coordinate

	yc=ycs;
}

// Operators
Point& Point::operator = (const Point& source)
{ // Assignment operator

	// Exit if same object
	if (this==&source) return *this;

	xc=source.xc;
	yc=source.yc;

	return *this;
}