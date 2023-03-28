// Observer.cpp
//
// (C) Datasim Education BV 2001

#include "Observer.hpp"

Observer::Observer(PropertyCommand& command)
{// Default constructor

	cmd = command;
}

Observer::~Observer()
{// Destructor
}

void Observer::execute(stringSubject* obj)
{

}


