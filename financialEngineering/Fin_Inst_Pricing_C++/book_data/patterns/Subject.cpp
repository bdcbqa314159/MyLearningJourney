// Subject.cpp
//
// (C) Datasim Education BV 2001

#include "Subject.hpp"
#include <functional>

// Default constructor
Subject::Subject(PropertyCommand& c) 
{

	cmd = c;
}

Subject::~Subject()
{// Destructor
}

void Subject::AddObserver(Observer* o, String cmdname)
{
	Observers.push_back(obj);
}

/*
void Subject::DeleteObserver(Observer* obj)
{

	Observers.remove(obj);
}

void Subject::NotifyObservers()
{
	std::list<Observer*>::iterator it;
	std::list<Observer*>::iterator end = Observers.end();

	for(it = Observers.begin(); it != end; it ++)
	{
		(*it)->Update(this);
	}
	
}

*/