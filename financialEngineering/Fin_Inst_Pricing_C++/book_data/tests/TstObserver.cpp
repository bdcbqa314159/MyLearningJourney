// TstObserver.cpp
//
// (C) Datasim Education BV 2001

#include "subject.hpp"
#include "Observer.hpp"

void main()
{
	// Create a Subject object
	Subject cnt;
	
	// Just increase the Subject without observing it
    cnt.IncreaseSubject();
	cnt.IncreaseSubject();
	cnt.IncreaseSubject();

	// Create an observer
	SubjectObserver observer1(cnt);

	// Increase the Subject
    cnt.IncreaseSubject();
	cnt.IncreaseSubject();
	cnt.IncreaseSubject();

	// Create another observer
	SubjectObserver observer2(cnt);

	// Increase the Subject
    cnt.IncreaseSubject();
	cnt.IncreaseSubject();
	cnt.IncreaseSubject();

	// remove the first observer
	cnt.DeleteObserver(&observer1);

	// Increase the Subject
    cnt.IncreaseSubject();
	cnt.IncreaseSubject();
	cnt.IncreaseSubject();

}

