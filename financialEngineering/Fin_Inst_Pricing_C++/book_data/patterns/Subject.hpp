// Subject.hpp
//
// (C) Datasim Education BV 2001

#ifndef Subject_HPP
#define Subject_HPP


#include "Observer.hpp"
#include "propertycommand.cpp"
#include <string>

class Subject
{
private:
	Observer* obs;
	string nam;
	PropertyComamnd cmd;

	Subject(const Subject& org);
	Subject& operator=(const Subject& org);

public:
	Subject(PropertyCommand& c);	// Default constructor
	virtual ~Subject();	// Destructor

	void AddObserver(pair<Observer*, string> obj);		// Add an observer to the list
//	void DeleteObserver(Observer* obj);		// Remove an observer from the list
//	void NotifyObservers();// Notify the observers
};

#endif

