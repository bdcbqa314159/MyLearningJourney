// Observer.hpp
//
// (C) Datasim Education BV 2001

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "propertycommand.cpp"

class Subject;

class Observer
{
private:
	Observer(const Observer& orig);	// Copy constructor
	Observer& operator=(const Observer& orig);	// Assignment operator

	PropertyComamnd cmd;

public:
	Observer(PropertyComamnd& commmand;);		// Default constructor
	~Observer();	// Destructor

	// Method is called when the obeservable object has a change in its state
	virtual void execute(string cmd);
};

#endif


