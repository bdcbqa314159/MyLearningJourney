// Observable.cpp
//
// (C) Datasim Education BV 2001

#include "Observable.hpp"
#include <iostream>
#include <list>

// Default constructor
Observable::Observable() 
{
}

Observable::~Observable()
{// Destructor
}

void Observable::AddObserver(Observer* obj)
{
	Observers.push_back(obj);
}

void Observable::DeleteObserver(Observer* obj)
{

	Observers.remove(obj);
}

void Observable::NotifyObservers()
{
	list<Observer*>::iterator it;

	cout << "\n**** Starting the broadcast\n";
	for(it = Observers.begin(); it != Observers.end(); it ++)
	{
		(*it)->Update(this);
	}
	
	cout << "\n**** Ending the broadcast\n";

}
