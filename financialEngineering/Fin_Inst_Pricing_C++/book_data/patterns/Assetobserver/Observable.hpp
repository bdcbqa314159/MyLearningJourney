// Observable.hpp
//
// The class of Subject in the observer pattern.
//
// (C) Datasim Education BV 2001-2004

#ifndef Observable_HPP
#define Observable_HPP

#include <list>
using namespace std;

#include "Observer.hpp"


class Observable // The Subject
{
private:
	std::list<Observer*> Observers;

	Observable(const Observable& org);
	Observable& operator=(const Observable& org);

public:
	Observable();	// Default constructor
	virtual ~Observable();	// Destructor

	void AddObserver(Observer* obj);		// Add an observer to the list
	void DeleteObserver(Observer* obj);		// Remove an observer from the list
	void NotifyObservers();// Notify the observers
};

#endif

