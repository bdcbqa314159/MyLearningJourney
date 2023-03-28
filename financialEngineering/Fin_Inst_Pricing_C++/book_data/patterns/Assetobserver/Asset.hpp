// Asset.hpp
//
// Basic class modelling stocks, for use in showing how
// the Observer pattern works.
//
// (C) Datasim Component Technology BV 2003-2004

#ifndef Asset_hpp
#define Asset_hpp

#include <iostream>

#include "observable.hpp"


class Asset : public Observable
{
private:
		double val;			// Asset value at this stage
public:

	Asset() {}

	void setStock (double newVal)
	{
		// Change propagation mechanism; tell everyone
		val = newVal;
		NotifyObservers();
	}

	double getStock() const {return val;}


};



#endif
