// pasctst.cxx
// Program to test the Pascal distributution.
//
// Problem statement.
// We consider an experiment in which the probability of success is 0.8.
// What is the expected number of repititions required when the experiment
// is repeated until 4 successful outcomes have occurred?
//
// Answer.
// This is an application of the Pascal distribution since we are
// interested in carrying out an experiment a number of times until
// something happens.

#include <iostream.h>
#include "pascal.hxx"

main()
{
	PASCAL random (0.8, 4);

	cout << "Number of repititions required: "
	     << random.expected();

	return 0;
}